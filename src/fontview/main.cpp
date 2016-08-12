#include <stdio.h>

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/filename.h>
#include <wx/gbsizer.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "fontview/name_table.h"
#include "fontview/font_style.h"
#include "fontview/font_var_axis.h"
#include "fontview/sample_text.h"
#include "fontview/text_settings.h"
#include "fontview/util.h"

using fontview::FontStyle;
using fontview::FontVarAxis;
using fontview::SampleText;
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
  MyFrame(const wxPoint& pos, const wxSize& size,
          TextSettings* textSettings);  // takes ownership
  virtual ~MyFrame();

 private:
  void OnOpen(wxCommandEvent& event);
  void OnClose(wxCommandEvent& event);
  void OnHello(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnFamilyChoiceChanged(wxCommandEvent& event);
  void OnStyleChoiceChanged(wxCommandEvent& event);
  void OnAxisSliderChanged(wxCommandEvent& event);
  void OnTextSettingsChanged();
  bool ShouldRebuildAxisSliders() const;
  void RebuildAxisSliders();

  wxDECLARE_EVENT_TABLE();
  std::unique_ptr<TextSettings> textSettings_;
  TextSettings::Listener textSettingsListener_;
  bool processingModelChange_;

  // These wxWidgets objects are owned by wxWidgets, not by us.
  SampleText* sampleText_;
  wxPanel* propertyPanel_;
  wxChoice* familyChoice_;
  wxChoice* styleChoice_;
  wxSpinCtrlDouble* sizeControl_;
  wxGridBagSizer* axisSizer_;

  struct AxisSlider {
    wxStaticText* title;
    wxSlider* slider;
    const FontVarAxis* axis;
  };
  std::vector<AxisSlider> axisSliders_;
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
    wxMessageBox("FontView does not understand "
                 "the format of the selected file.",
                 "Unsupported File Format", wxOK | wxICON_ERROR);
    return;
  }

  ++numDocuments_;
  wxPoint pos(16 * numDocuments_, 20 + 16 * numDocuments_);
  MyFrame* frame = new MyFrame(pos, wxSize(600, 340),
                               textSettings.release());
  frame->Show(true);
}

bool MyApp::OnInit() {
  SetAppDisplayName(wxT("FontView"));
  if (FT_Init_FreeType(&freeTypeLibrary_)) {
    wxMessageBox("The FreeType library could not be initialized.",
                 "FreeType Error", wxOK | wxICON_ERROR);
    wxExit();
  }

  return OpenFontFile(NULL);
}

MyFrame::MyFrame(const wxPoint& pos, const wxSize& size,
                 TextSettings* textSettings)
  : wxFrame(NULL, wxID_ANY, "", pos, size),
    textSettings_(textSettings),
    textSettingsListener_([this]() { this->OnTextSettingsChanged(); }),
    sampleText_(NULL), propertyPanel_(NULL),
    familyChoice_(NULL), styleChoice_(NULL), sizeControl_(NULL),
    axisSizer_(new wxGridBagSizer(0, 4)) {
  textSettings_->AddListener(&textSettingsListener_);

  wxMenu* fileMenu = new wxMenu();
  fileMenu->Append(wxID_NEW);
  fileMenu->Enable(wxID_NEW, false);
  fileMenu->Append(wxID_OPEN);
  fileMenu->Append(wxID_CLOSE);
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_EXIT);
  wxMenu* helpMenu = new wxMenu();
  helpMenu->Append(wxID_ABOUT, wxT("About FontView"));
  wxMenuBar* menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, "&File");
  menuBar->Append(helpMenu, "&Help");
  SetMenuBar(menuBar);

  wxPanel* framePanel = new wxPanel(this);
  sampleText_ = new SampleText(framePanel);
  sampleText_->SetText("The quick brown fox jumps over the lazy dog.");
  propertyPanel_ = new wxPanel(framePanel);
  wxPanel* stylePanel = new wxPanel(propertyPanel_);
  wxBoxSizer* framePanelSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* propertyPanelSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* stylePanelSizer = new wxBoxSizer(wxHORIZONTAL);

  sampleText_->SetBackgroundColour(wxColour(wxT("#ffffff")));

  framePanel->SetSizer(framePanelSizer);
  framePanelSizer->Add(sampleText_, 1, wxEXPAND | wxALL, 0);
  framePanelSizer->Add(propertyPanel_, 0, wxEXPAND | wxALL, 20);

  propertyPanel_->SetSizer(propertyPanelSizer);
  stylePanel->SetSizer(stylePanelSizer);

  std::vector<wxString> familyChoices;
  for (const std::string family : textSettings_->GetFamilies()) {
    familyChoices.push_back(wxString(family));
  }

  familyChoice_ =
    new wxChoice(propertyPanel_, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                 familyChoices.size(), &familyChoices.front());
  propertyPanelSizer->Add(familyChoice_, 0, wxEXPAND | wxALL, 0);
  propertyPanelSizer->AddSpacer(10);
  propertyPanelSizer->Add(stylePanel, 0, wxEXPAND | wxALL, 0);
  propertyPanelSizer->Add(axisSizer_, 0, wxEXPAND | wxHORIZONTAL, 0);

  styleChoice_ = new wxChoice(stylePanel, wxID_ANY);
  stylePanelSizer->Add(styleChoice_, 1, wxEXPAND | wxALL, 0);
  stylePanelSizer->AddSpacer(10);
  sizeControl_ = new wxSpinCtrlDouble(
    stylePanel, wxID_ANY, wxT("12"), wxDefaultPosition, wxDefaultSize,
    wxSP_ARROW_KEYS, 1, 999, 12, 0.5);
  sizeControl_->SetMaxSize(wxSize(60, -1));
  sizeControl_->SetDigits(1);  // 1 digit fractional precision, eg. 12.5 pt.
  stylePanelSizer->Add(sizeControl_, 0, wxALL, 0);

  axisSizer_->Add(0, 15, wxGBPosition(0, 0), wxDefaultSpan);  // Spacer above.
  axisSizer_->Add(0, 15, wxGBPosition(0, 1), wxDefaultSpan);  // Spacer above.
  axisSizer_->AddGrowableCol(0, 0);

  OnTextSettingsChanged();
  familyChoice_->Bind(wxEVT_CHOICE, &MyFrame::OnFamilyChoiceChanged, this);
  styleChoice_->Bind(wxEVT_CHOICE, &MyFrame::OnStyleChoiceChanged, this);
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
  processingModelChange_ = true;
  sampleText_->SetFontFace(textSettings_->GetFace());
  wxFileName filename(textSettings_->GetFontContainer());
  SetTitle(filename.GetFullName());

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
    if (style == curStyle &&
        style->GetVariation() == textSettings_->GetVariation()) {
      curStyleIndex = static_cast<int>(styleChoice_->GetCount());
    }
    styleChoice_->Append(style->GetStyleName(), static_cast<void*>(style));
  }
  if (curStyleIndex >= 0) {
    styleChoice_->SetSelection(curStyleIndex);
  } else {
    // TODO: At least on MacOS, we should add a separator line here.
    // However, wxWidgets does not support separators inside wxChoices yet.
    // https://groups.google.com/forum/#!topic/wxpython-users/1q0M0xTHpv8
    // http://www.yqcomputer.com/1171_2386_1.htm
    // http://trac.wxwidgets.org/ticket/11130
    //
    // http://trac.wxwidgets.org/ticket/10438
    // (This ticket claims that "-" produces a separator on OSX,
    // but this does not actually work on MacOS X 10.11.6)
    //
    // styleChoice_->Append(std::string("-"), static_cast<void*>(NULL));
    styleChoice_->Append(std::string("Custom"), static_cast<void*>(NULL));
    styleChoice_->SetSelection(styleChoice_->GetCount() - 1);
  }

  if (ShouldRebuildAxisSliders()) {
    RebuildAxisSliders();
  }

  const FontStyle::Variation& var = textSettings_->GetVariation();
  for (const AxisSlider& s : axisSliders_) {
    FontStyle::Variation::const_iterator iter = var.find(s.axis->GetTag());
    if (iter != var.end() && s.axis->GetMinValue() < s.axis->GetMaxValue()) {
      double fraction = (iter->second - s.axis->GetMinValue()) /
	(s.axis->GetMaxValue() - s.axis->GetMinValue());
      fraction = fontview::clamp(fraction, 0.0, 1.0);
      s.slider->SetValue(static_cast<int>(fraction * 1000000));
    }
  }

  processingModelChange_ = false;
}

// Find out if we need to rebuild the axis sliders. We avoid rebuilding
// because this would disrupt the user experience while dragging a slider.
bool MyFrame::ShouldRebuildAxisSliders() const {
  FontStyle* curStyle = textSettings_->GetStyle();
  if (curStyle == NULL) {
    return !axisSliders_.empty();
  }

  const std::vector<FontVarAxis*>& axes = curStyle->GetAxes();
  if (axes.size() != axisSliders_.size()) {
    return true;
  }

  for (size_t i = 0; i < axes.size(); ++i) {
    if (axes[i] != axisSliders_[i].axis) {
      return true;
    }
  }

  return false;
}

void MyFrame::RebuildAxisSliders() {
  for (const AxisSlider& s : axisSliders_) {
    axisSizer_->Detach(s.title);
    axisSizer_->Detach(s.slider);
    s.title->Destroy();
    s.slider->Destroy();
  }
  axisSliders_.clear();

  FontStyle* curStyle = textSettings_->GetStyle();
  if (curStyle) {
    int row = 1;  // we have a spacer at (0, 0)
    for (const FontVarAxis* axis : curStyle->GetAxes()) {
      std::string title(axis->GetName());
      title.append(":");
      AxisSlider s;
      s.axis = axis;
      s.title = new wxStaticText(propertyPanel_, wxID_ANY, title);
      s.slider = new wxSlider(propertyPanel_, wxID_ANY, 0, 0, 1000000);
      axisSliders_.push_back(s);
      axisSizer_->Add(s.title, wxGBPosition(row, 0), wxDefaultSpan);
      axisSizer_->Add(s.slider, wxGBPosition(row, 1), wxDefaultSpan);
      s.slider->Bind(wxEVT_SLIDER, &MyFrame::OnAxisSliderChanged, this);
      ++row;
    }
  }
  axisSizer_->Layout();
}

void MyFrame::OnFamilyChoiceChanged(wxCommandEvent& event) {
  if (!processingModelChange_) {
    const std::string family = event.GetString().ToStdString();
    textSettings_->SetFamily(family);
  }
}

void MyFrame::OnStyleChoiceChanged(wxCommandEvent& event) {
  if (!processingModelChange_) {
    FontStyle* style = static_cast<FontStyle*>(event.GetClientData());
    if (style) {
      textSettings_->SetStyle(style);
    }
  }
}

void MyFrame::OnAxisSliderChanged(wxCommandEvent& event) {
  FontStyle::Variation var;
  for (const AxisSlider& s : axisSliders_) {
    double range = s.axis->GetMaxValue() - s.axis->GetMinValue();
    double fraction = static_cast<double>(s.slider->GetValue()) / 1000000;
    double value = s.axis->GetMinValue() + fraction * range;
    var[s.axis->GetTag()] = value;
  }
  textSettings_->SetVariation(var);
}

wxIMPLEMENT_APP(MyApp);
