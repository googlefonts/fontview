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

using fontview::BuildNameTable;
using fontview::FontStyle;
using fontview::GetFontName;
using fontview::GetFontFamilyName;
using fontview::NameTable;

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
          std::vector<FT_Face>* faces);
  virtual ~MyFrame();

 private:
  void OnOpen(wxCommandEvent& event);
  void OnClose(wxCommandEvent& event);
  void OnHello(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnFamilyChanged(wxCommandEvent& event);

  wxDECLARE_EVENT_TABLE();
  std::unique_ptr<std::vector<FT_Face>> faces_;
  std::vector<NameTable*> faceNames_;
  std::vector<FontStyle*> fontStyles_;
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

std::vector<FT_Face>* LoadFaces(const std::string& path) {
  std::vector<FT_Face>* faces = new std::vector<FT_Face>();
  FT_Long numFaces = 0;
  FT_Face face = NULL;
  FT_Error error = FT_New_Face(freeTypeLibrary_, path.c_str(), -1, &face);
  if (face) {
    if (!error) {
      numFaces = face->num_faces;
    }
    FT_Done_Face(face);
  }
  for (FT_Long faceIndex = 0; faceIndex < numFaces; ++faceIndex) {
    face = NULL;
    if (FT_New_Face(freeTypeLibrary_, path.c_str(), faceIndex, &face)) {
      continue;
    }
    faces->push_back(face);
  }
  return faces;
}

MyApp::MyApp()
  : numDocuments_(0) {
}

bool MyApp::OpenFontFile(wxWindow* parent) {
  const wxString path = wxLoadFileSelector(
      wxT("font"), wxT("otf;ttf;otc;ttc"),  // what, extensions
      wxEmptyString, parent);  // default_name, parent
  if (path.empty()) {
    return false;
  } else {
    MacOpenFile(path);
    return true;
  }
}

void MyApp::MacOpenFile(const wxString& path) {
  std::unique_ptr<std::vector<FT_Face>> faces(LoadFaces(path.ToStdString()));
  if (!faces.get() || faces->empty()) {
    wxMessageBox("Morphable Type does not understand "
                 "the format of the selected file.",
                 "Unsupported File Format", wxOK | wxICON_ERROR);
    return;
  }

  ++numDocuments_;
  wxPoint pos(16 * numDocuments_, 20 + 16 * numDocuments_);
  wxFileName filename(path);
  MyFrame* frame = new MyFrame(filename.GetFullName(), pos, wxSize(600, 340),
                               faces.release());
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
                 std::vector<FT_Face>* faces)
  : wxFrame(NULL, wxID_ANY, title, pos, size),
    faces_(faces), faceNames_(),
    familyChoice_(NULL), styleChoice_(NULL), sizeControl_(NULL) {
  for (size_t i = 0; i < faces->size(); ++i) {
    NameTable* names = BuildNameTable(faces->at(i));
    faceNames_.push_back(names);
  }

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

  std::set<std::string> families;
  std::string firstFamily;
  for (size_t i = 0; i < faceNames_.size(); ++i) {
    const NameTable& nameTable = *faceNames_[i];
    const std::string& familyName = GetFontFamilyName(nameTable);
    if (!familyName.empty()) {
      families.insert(familyName);
      if (firstFamily.empty()) {
        firstFamily = familyName;
      }
    }
  }

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
  for (const std::string family : families) {
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

  if (!firstFamily.empty()) {
    wxCommandEvent event;
    event.SetString(firstFamily);
    OnFamilyChanged(event);
  }
  familyChoice_->Bind(wxEVT_CHOICE, &MyFrame::OnFamilyChanged, this);
}

MyFrame::~MyFrame() {
  for (FontStyle* style : fontStyles_) {
    delete style;
  }
  for (NameTable* table : faceNames_) {
    delete table;
  }
  for (FT_Face face : *faces_) {
    FT_Done_Face(face);
  }
  faces_->clear();
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

void MyFrame::OnFamilyChanged(wxCommandEvent& event) {
  const std::string family = event.GetString().ToStdString();
  styleChoice_->Clear();
  for (FontStyle* style : fontStyles_) {
    delete style;
  }
  fontStyles_.clear();

  if (family.empty()) {
    return;
  }

  for (size_t faceIndex = 0; faceIndex < faces_->size(); ++faceIndex) {
    FT_Face face = faces_->at(faceIndex);
    const NameTable& names = *faceNames_[faceIndex];
    if (family != GetFontFamilyName(names)) {
      continue;
    }
    for (FontStyle* style : FontStyle::GetStyles(face, names)) {
      fontStyles_.push_back(style);
      styleChoice_->Append(style->GetName(), static_cast<void*>(style));
    }
  }
}

wxIMPLEMENT_APP(MyApp);
