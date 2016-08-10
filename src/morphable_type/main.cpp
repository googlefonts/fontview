#include <stdio.h>

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/filename.h>
#include <wx/spinctrl.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H

#include "name_table.h"
#include "font_style.h"
#include "text_settings.h"

using fontview::BuildNameTable;
using fontview::FontStyle;
using fontview::GetFontName;
using fontview::GetFontFamilyName;
using fontview::NameTable;
using fontview::TextSettings;


class MyApp : public wxApp {
 public:
  MyApp();
  virtual bool OnInit();

  virtual void MacOpenFile(const wxString& fileName);
  bool OpenFontFile(wxWindow* parent);

 private:
  int numDocuments_;
};


class MyFrame : public wxFrame {
 public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
          TextSettings* textSettings);  // takes ownership
  virtual ~MyFrame();

 private:
  void OnOpen(wxCommandEvent& event);
  void OnClose(wxCommandEvent& event);
  void OnHello(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnFamilyChanged(wxCommandEvent& event);
  void OnTextSettingsChanged();

  wxDECLARE_EVENT_TABLE();
  std::unique_ptr<TextSettings> textSettings_;
  TextSettings::Listener textSettingsListener_;
  bool processingModelChange_;

  wxChoice* familyChoice_;
  wxChoice* styleChoice_;
  wxSpinCtrlDouble* sizeControl_;
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_OPEN,  MyFrame::OnOpen)
EVT_MENU(wxID_CLOSE, MyFrame::OnClose)
EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

static FT_Library freeTypeLibrary_ = NULL;

namespace fontview {
FT_Library GetFreeTypeLibrary() {
  return freeTypeLibrary_;
}
}  // namespace fontview

MyApp::MyApp()
  : numDocuments_(0) {
}

bool MyApp::OpenFontFile(wxWindow* parent) {
  const wxString path = wxLoadFileSelector(
      wxT("font"), wxT("otf;ttf;otc;ttc;pfb"),  // what, extensions
      wxEmptyString, parent);  // default_name, parent
  if (path.empty()) {
    return false;
  } else {
    MacOpenFile(path);
    return true;
  }
}

void MyApp::MacOpenFile(const wxString& path) {
  std::unique_ptr<TextSettings> textSettings(new TextSettings());
  if (!textSettings->SetFontContainer(path.ToStdString())) {
    wxMessageBox("Morphable Type does not understand "
                 "the format of the selected file.",
                 "Unsupported File Format", wxOK | wxICON_ERROR);
    return;
  }

  ++numDocuments_;
  wxPoint pos(16 * numDocuments_, 20 + 16 * numDocuments_);
  wxFileName filename(path);
  MyFrame* frame = new MyFrame(filename.GetFullName(), pos, wxSize(600, 340),
                               textSettings.release());
  frame->Show(true);
}

bool MyApp::OnInit() {
  SetAppDisplayName(wxT("Morphable Type"));
  if (FT_Init_FreeType(&freeTypeLibrary_)) {
    wxMessageBox("The FreeType library could not be initialized.",
                 "FreeType Error", wxOK | wxICON_ERROR);
    wxExit();
  }

  return OpenFontFile(NULL);
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                 TextSettings* textSettings)
  : wxFrame(NULL, wxID_ANY, title, pos, size),
    textSettings_(textSettings),
    textSettingsListener_([this]() { this->OnTextSettingsChanged(); }),
    familyChoice_(NULL), styleChoice_(NULL), sizeControl_(NULL) {
  textSettings_->AddListener(&textSettingsListener_);

  wxMenu* fileMenu = new wxMenu();
  fileMenu->Append(wxID_NEW);
  fileMenu->Enable(wxID_NEW, false);
  fileMenu->Append(wxID_OPEN);
  fileMenu->Append(wxID_CLOSE);
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_EXIT);
  wxMenu* helpMenu = new wxMenu();
  helpMenu->Append(wxID_ABOUT, wxT("About Morphable Type"));
  wxMenuBar* menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, "&File");
  menuBar->Append(helpMenu, "&Help");
  SetMenuBar(menuBar);

  wxPanel* framePanel = new wxPanel(this);
  wxPanel* textPanel = new wxPanel(framePanel);
  wxPanel* propertyPanel = new wxPanel(framePanel);
  wxPanel* stylePanel = new wxPanel(propertyPanel);
  wxBoxSizer* framePanelSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* propertyPanelSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* stylePanelSizer = new wxBoxSizer(wxHORIZONTAL);

  textPanel->SetBackgroundColour(wxColour(wxT("#ffffff")));

  framePanel->SetSizer(framePanelSizer);
  framePanelSizer->Add(textPanel, 1, wxEXPAND | wxALL, 0);
  framePanelSizer->Add(propertyPanel, 0, wxEXPAND | wxALL, 20);

  propertyPanel->SetSizer(propertyPanelSizer);
  stylePanel->SetSizer(stylePanelSizer);

  std::vector<wxString> familyChoices;
  for (const std::string family : textSettings_->GetFamilies()) {
    familyChoices.push_back(wxString(family));
  }

  familyChoice_ =
    new wxChoice(propertyPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                 familyChoices.size(), &familyChoices.front());
  propertyPanelSizer->Add(familyChoice_, 0, wxEXPAND | wxALL, 0);
  propertyPanelSizer->AddSpacer(10);
  propertyPanelSizer->Add(stylePanel, 0, wxEXPAND | wxALL, 0);

  styleChoice_ = new wxChoice(stylePanel, wxID_ANY);
  stylePanelSizer->Add(styleChoice_, 1, wxEXPAND | wxALL, 0);
  stylePanelSizer->AddSpacer(10);
  sizeControl_ = new wxSpinCtrlDouble(
    stylePanel, wxID_ANY, wxT("12"), wxDefaultPosition, wxDefaultSize,
    wxSP_ARROW_KEYS, 1, 999, 12, 0.5);
  sizeControl_->SetMaxSize(wxSize(60, -1));
  stylePanelSizer->Add(sizeControl_, 0, wxALL, 0);
  OnTextSettingsChanged();
  familyChoice_->Bind(wxEVT_CHOICE, &MyFrame::OnFamilyChanged, this);
}

MyFrame::~MyFrame() {
  textSettings_->RemoveListener(&textSettingsListener_);
}

void MyFrame::OnOpen(wxCommandEvent& event) {
  static_cast<MyApp*>(wxTheApp)->OpenFontFile(this);
}

void MyFrame::OnClose(wxCommandEvent& event) {
  Close(true);
}

void MyFrame::OnExit(wxCommandEvent& event) {
  wxExit();
}

void MyFrame::OnAbout(wxCommandEvent& event) {
  wxAboutDialogInfo info;
  info.SetCopyright(
      wxT("Copyright © 2016 Google, Inc. All rights reserved.\n"
          "Licensed under the Apache License, Version 2.0."));
  wxAboutBox(info);
}

void MyFrame::OnTextSettingsChanged() {
  printf("MyFrame::OnTextSettingsChanged\n"
         "  family: %s\n", textSettings_->GetFamily().c_str());

  processingModelChange_ = true;
  familyChoice_->Clear();
  for (const std::string& family : textSettings_->GetFamilies()) {
    familyChoice_->Append(wxString(family));
  }
  familyChoice_->SetStringSelection(textSettings_->GetFamily());

  std::vector<FontStyle*> styles;
  for (FontStyle* style : textSettings_->GetStyles()) {
    if (style->GetFamilyName() == textSettings_->GetFamily()) {
      styles.push_back(style);
    }
  }
  std::sort(styles.begin(), styles.end(),
            [](const FontStyle* a, const FontStyle* b) {
      double va = a->GetWeight(), vb = b->GetWeight();
      if (va < vb) return true; else if (va > vb) return false;
      va = a->GetWidth(); vb = b->GetWidth();
      if (va < vb) return true; else if (va > vb) return false;
      va = a->GetSlant(); vb = b->GetSlant();
      if (va < vb) return true; else if (va > vb) return false;
      return a->GetStyleName() < b->GetStyleName();
  });

  styleChoice_->Clear();
  int curStyleIndex = -1;
  FontStyle* curStyle = textSettings_->GetStyle();
  for (FontStyle* style : styles) {
    if (style == curStyle) {
      curStyleIndex = static_cast<int>(styleChoice_->GetCount());
    }
    styleChoice_->Append(style->GetStyleName(), static_cast<void*>(style));
  }
  if (curStyleIndex >= 0) {
    styleChoice_->SetSelection(curStyleIndex);
  }

  processingModelChange_ = false;
}

void MyFrame::OnFamilyChanged(wxCommandEvent& event) {
  if (!processingModelChange_) {
    const std::string family = event.GetString().ToStdString();
    textSettings_->SetFamily(family);
  }
}

wxIMPLEMENT_APP(MyApp);
