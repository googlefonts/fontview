/*
 * Copyright 2016 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/cmdline.h>
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
  virtual void OnInitCmdLine(wxCmdLineParser& parser);
  virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

  virtual void MacNewFile() ;
  virtual void MacOpenFile(const wxString& fileName);
  
  bool OpenFontFile(wxWindow* parent);
  const std::string& GetDefaultSampleText() const { return defaultSampleText_; }

 private:
  int numDocuments_;
  std::string defaultSampleText_;
};


class MyFrame : public wxFrame {
 public:
  MyFrame(const wxPoint& pos, const wxSize& size,
          TextSettings* textSettings);  // takes ownership
  virtual ~MyFrame();

 private:
  void OnOpen(wxCommandEvent& event);
  void OnClose(wxCommandEvent& event);
  void OnChangeSampleText(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnFamilyChoiceChanged(wxCommandEvent& event);
  void OnStyleChoiceChanged(wxCommandEvent& event);
  void OnLanguageChoiceChanged(wxCommandEvent& event);
  void OnFontSizeFieldChanged(wxSpinDoubleEvent& event);
  void OnAxisSliderChanged(wxCommandEvent& event);
  void OnTextSettingsChanged();

  void RebuildFamilyChoice();
  void RebuildStyleChoice();
  bool ShouldRebuildAxisSliders() const;
  void RebuildAxisSliders();
  void RebuildLanguageChoice();

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
  wxChoice* languageChoice_;

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
  : numDocuments_(0),
    defaultSampleText_("The quick brown fox jumps over the lazy dog.") {
}

bool MyApp::OpenFontFile(wxWindow* parent) {
  const wxString path = wxFileSelector(
      wxT("Load font file"),
      wxEmptyString, wxEmptyString, wxEmptyString,
      wxT("Font files (*.ttf, *.otf, *.otc, *.ttc, *.pfb, *.pfa)"
          "|*.ttf;*.otf;*.otc;*.ttc;*.pfb;*.pfa"),
      wxFD_OPEN | wxFD_FILE_MUST_EXIST,
      parent);
  if (path.empty()) {
    return false;
  } else {
    MacOpenFile(path);
    return true;
  }
}

void MyApp::MacNewFile() {
  OpenFontFile(NULL);
}

void MyApp::MacOpenFile(const wxString& path) {
  std::unique_ptr<TextSettings> textSettings(
      new TextSettings(defaultSampleText_));
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

  return wxApp::OnInit();
}

void MyApp::OnInitCmdLine(wxCmdLineParser& parser) {
  parser.AddOption(wxT("t"), wxT("text"), wxT("sample text"));
  parser.AddParam(wxT("font.otf"), wxCMD_LINE_VAL_STRING,
		  wxCMD_LINE_PARAM_MULTIPLE);
}

bool MyApp::OnCmdLineParsed(wxCmdLineParser& parser) {
  wxString sampleText;
  if (parser.Found("t", &sampleText) && !sampleText.empty()) {
    defaultSampleText_.assign(sampleText.ToStdString());
  }

  for (size_t i = 0; i < parser.GetParamCount(); ++i) {
    const std::string param = parser.GetParam(i).ToStdString();
    MacOpenFile(param.c_str());
  }

  // On MacOS, we show the file-opening dialog upon receiving an AppleEvent.
#if !(defined(__WXOSX__) &&__WXOSX__)
  if (numDocuments_ == 0) {
    return OpenFontFile(NULL);
  }
#endif

  return true;
}


MyFrame::MyFrame(const wxPoint& pos, const wxSize& size,
                 TextSettings* textSettings)
  : wxFrame(NULL, wxID_ANY, "", pos, size),
    textSettings_(textSettings),
    textSettingsListener_([this]() { this->OnTextSettingsChanged(); }),
    sampleText_(NULL), propertyPanel_(NULL),
    familyChoice_(NULL), styleChoice_(NULL), sizeControl_(NULL),
    axisSizer_(new wxGridBagSizer(0, 4)),
    languageChoice_(NULL) {
  textSettings_->AddListener(&textSettingsListener_);

  wxMenu* fileMenu = new wxMenu();
  fileMenu->Append(wxID_NEW);
  fileMenu->Enable(wxID_NEW, false);
  fileMenu->Append(wxID_OPEN);
  fileMenu->Append(wxID_CLOSE, wxT("Close\tCtrl+W"));
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_EXIT);

  wxMenu* editMenu = new wxMenu();
  editMenu->Append(wxID_UNDO);
  editMenu->Enable(wxID_UNDO, false);
  editMenu->Append(wxID_REDO);
  editMenu->Enable(wxID_REDO, false);
  editMenu->AppendSeparator();
  editMenu->Append(wxID_CUT);
  editMenu->Enable(wxID_CUT, false);
  editMenu->Append(wxID_COPY);
  editMenu->Enable(wxID_COPY, false);
  editMenu->Append(wxID_PASTE);
  editMenu->Enable(wxID_PASTE, false);
  editMenu->Append(wxID_CLEAR);
  editMenu->Enable(wxID_CLEAR, false);
  editMenu->AppendSeparator();
  wxMenuItem* changeSampleText =
      editMenu->Append(wxID_ANY, "Change Sample Text...\tCtrl+T");
  editMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnChangeSampleText, this, changeSampleText->GetId());

  wxMenu* helpMenu = new wxMenu();
  helpMenu->Append(wxID_ABOUT, wxT("About FontView"));
  wxMenuBar* menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, "&File");
  menuBar->Append(editMenu, "&Edit");
  menuBar->Append(helpMenu, "&Help");
  SetMenuBar(menuBar);

  wxPanel* framePanel = new wxPanel(this);
  sampleText_ = new SampleText(framePanel);
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
  propertyPanelSizer->AddSpacer(10);
  languageChoice_ = new wxChoice(propertyPanel_, wxID_ANY);
  propertyPanelSizer->Add(languageChoice_, 0, wxEXPAND | wxALL, 0);

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
  languageChoice_->Bind(wxEVT_CHOICE, &MyFrame::OnLanguageChoiceChanged, this);
  sizeControl_->Bind(wxEVT_SPINCTRLDOUBLE, &MyFrame::OnFontSizeFieldChanged,
                     this);
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

// TODO: Replace the modal dialog with direct manipulation.
// The current user interface is rather terrible, but it took
// just a few minutes to implement.
void MyFrame::OnChangeSampleText(wxCommandEvent& event) {
  wxTextEntryDialog dialog(this, "Please enter the new sample text:",
			   "Change Sample Text", sampleText_->GetText());
  if (dialog.ShowModal() != wxID_OK) {
    return;
  }
  sampleText_->SetText(dialog.GetValue().ToStdString(), true);
  sampleText_->Paint();
}

void MyFrame::OnAbout(wxCommandEvent& event) {
  wxAboutDialogInfo info;

#ifdef FONTVIEW_VERSION
#define VERSION_str(s) #s
#define VERSION_xstr(s) VERSION_str(s)
  const char* version = VERSION_xstr(FONTVIEW_VERSION);
  if (version && *version) {
    info.SetVersion(wxString(version));
  }
#endif

  info.SetCopyright(
      wxT("Copyright © 2016 Google, Inc. All rights reserved.\n"
          "Licensed under the Apache License, Version 2.0."));
  wxAboutBox(info);
}

void MyFrame::OnTextSettingsChanged() {
  processingModelChange_ = true;
  sampleText_->SetFontFace(textSettings_->GetFace());
  sampleText_->SetFontSize(textSettings_->GetFontSize());
  sampleText_->SetTextLanguage(textSettings_->GetTextLanguage());
  wxFileName filename(textSettings_->GetFontContainer());
  SetTitle(filename.GetFullName());

  RebuildFamilyChoice();
  RebuildStyleChoice();
  if (ShouldRebuildAxisSliders()) {
    RebuildAxisSliders();
  }
  RebuildLanguageChoice();

  const FontStyle::Variation& var = textSettings_->GetVariation();
  for (const AxisSlider& s : axisSliders_) {
    FontStyle::Variation::const_iterator iter = var.find(s.axis->GetTag());
    if (iter != var.end() && s.axis->GetMinValue() < s.axis->GetMaxValue()) {
      double fraction = (iter->second - s.axis->GetMinValue()) /
	(s.axis->GetMaxValue() - s.axis->GetMinValue());
      fraction = fontview::clamp(fraction, 0.0, 1.0);
      s.slider->SetRange(0, 1000);
      s.slider->SetValue(static_cast<int>(fraction * 1000));
    }
  }

  sizeControl_->SetValue(textSettings_->GetFontSize());
  if (sampleText_) {
    FontStyle* curStyle = textSettings_->GetStyle();
    if (!sampleText_->HasCustomText() && curStyle) {
      sampleText_->SetText(curStyle->GetSampleText(), false);
    }
    sampleText_->Paint();
  }

  processingModelChange_ = false;
}

void MyFrame::RebuildFamilyChoice() {
  familyChoice_->Clear();
  for (const std::string& family : textSettings_->GetFamilies()) {
    familyChoice_->Append(wxString(family));
  }
  familyChoice_->SetStringSelection(textSettings_->GetFamily());
}

void MyFrame::RebuildStyleChoice() {
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
      va = a->GetSlant(); vb = b->GetSlant();  // negative = right-leaning
      if (va > vb) return true; else if (va < vb) return false;
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
      s.slider = new wxSlider(propertyPanel_, wxID_ANY, 0, 0, 1000);
      wxSize size = s.slider->GetBestSize();
      if (size.x < 200) {
	size.x = 200;
      }
      s.slider->SetMinSize(size);
      axisSliders_.push_back(s);
      axisSizer_->Add(s.title, wxGBPosition(row, 0), wxDefaultSpan);
      axisSizer_->Add(s.slider, wxGBPosition(row, 1), wxDefaultSpan);
      s.slider->Bind(wxEVT_SLIDER, &MyFrame::OnAxisSliderChanged, this);
      ++row;
    }
  }
  axisSizer_->Layout();
}


// HarfBuzz returns language tags in lowercase. This is not the
// canonical form for region and script codes. But since we do not
// display the codes to users, we don’t bother to work around
// HarfBuzz.
static const std::map<std::string, std::string> languageNames = {
  {"und-fonipa", "International Phonetic Alphabet"},
  {"und-fonnapa", "North American Phonetic Alphabet"},

  // TODO: Remove this once HarfBuzz returns proper BCP47 codes.
  {"mo", "Moldavian"},  // deprecated; should be ro-MD

  // http://www.unicode.org/repos/cldr/trunk/common/main/en.xml
  {"aa", "Afar"},
  {"ab", "Abkhazian"},
  {"ace", "Achinese"},
  {"ach", "Acoli"},
  {"ada", "Adangme"},
  {"ady", "Adyghe"},
  {"ae", "Avestan"},
  {"aeb", "Tunisian Arabic"},
  {"af", "Afrikaans"},
  {"afh", "Afrihili"},
  {"agq", "Aghem"},
  {"ain", "Ainu"},
  {"ak", "Akan"},
  {"akk", "Akkadian"},
  {"akz", "Alabama"},
  {"ale", "Aleut"},
  {"aln", "Gheg Albanian"},
  {"alt", "Southern Altai"},
  {"am", "Amharic"},
  {"an", "Aragonese"},
  {"ang", "Old English"},
  {"anp", "Angika"},
  {"ar", "Arabic"},
  {"arc", "Aramaic"},
  {"arn", "Mapuche"},
  {"aro", "Araona"},
  {"arp", "Arapaho"},
  {"arq", "Algerian Arabic"},
  {"ars", "Najdi Arabic"},
  {"arw", "Arawak"},
  {"ary", "Moroccan Arabic"},
  {"arz", "Egyptian Arabic"},
  {"as", "Assamese"},
  {"asa", "Asu"},
  {"ase", "American Sign Language"},
  {"ast", "Asturian"},
  {"av", "Avaric"},
  {"avk", "Kotava"},
  {"awa", "Awadhi"},
  {"ay", "Aymara"},
  {"az", "Azerbaijani"},
  {"ba", "Bashkir"},
  {"bal", "Baluchi"},
  {"ban", "Balinese"},
  {"bar", "Bavarian"},
  {"bas", "Basaa"},
  {"bax", "Bamun"},
  {"bbc", "Batak Toba"},
  {"bbj", "Ghomala"},
  {"be", "Belarusian"},
  {"bej", "Beja"},
  {"bem", "Bemba"},
  {"bew", "Betawi"},
  {"bez", "Bena"},
  {"bfd", "Bafut"},
  {"bfq", "Badaga"},
  {"bg", "Bulgarian"},
  {"bgn", "Western Balochi"},
  {"bho", "Bhojpuri"},
  {"bi", "Bislama"},
  {"bik", "Bikol"},
  {"bin", "Bini"},
  {"bjn", "Banjar"},
  {"bkm", "Kom"},
  {"bla", "Siksika"},
  {"bm", "Bambara"},
  {"bn", "Bangla"},
  {"bo", "Tibetan"},
  {"bpy", "Bishnupriya"},
  {"bqi", "Bakhtiari"},
  {"br", "Breton"},
  {"bra", "Braj"},
  {"brh", "Brahui"},
  {"brx", "Bodo"},
  {"bs", "Bosnian"},
  {"bss", "Akoose"},
  {"bua", "Buriat"},
  {"bug", "Buginese"},
  {"bum", "Bulu"},
  {"byn", "Blin"},
  {"byv", "Medumba"},
  {"ca", "Catalan"},
  {"cad", "Caddo"},
  {"car", "Carib"},
  {"cay", "Cayuga"},
  {"cch", "Atsam"},
  {"ce", "Chechen"},
  {"ceb", "Cebuano"},
  {"cgg", "Chiga"},
  {"ch", "Chamorro"},
  {"chb", "Chibcha"},
  {"chg", "Chagatai"},
  {"chk", "Chuukese"},
  {"chm", "Mari"},
  {"chn", "Chinook Jargon"},
  {"cho", "Choctaw"},
  {"chp", "Chipewyan"},
  {"chr", "Cherokee"},
  {"chy", "Cheyenne"},
  {"ckb", "Central Kurdish"},
  {"co", "Corsican"},
  {"cop", "Coptic"},
  {"cps", "Capiznon"},
  {"cr", "Cree"},
  {"crh", "Crimean Turkish"},
  {"crs", "Seselwa Creole French"},
  {"cs", "Czech"},
  {"csb", "Kashubian"},
  {"cu", "Church Slavic"},
  {"cv", "Chuvash"},
  {"cy", "Welsh"},
  {"da", "Danish"},
  {"dak", "Dakota"},
  {"dar", "Dargwa"},
  {"dav", "Taita"},
  {"de", "German"},
  {"del", "Delaware"},
  {"den", "Slave"},
  {"dgr", "Dogrib"},
  {"din", "Dinka"},
  {"dje", "Zarma"},
  {"doi", "Dogri"},
  {"dsb", "Lower Sorbian"},
  {"dtp", "Central Dusun"},
  {"dua", "Duala"},
  {"dum", "Middle Dutch"},
  {"dv", "Divehi"},
  {"dyo", "Jola-Fonyi"},
  {"dyu", "Dyula"},
  {"dz", "Dzongkha"},
  {"dzg", "Dazaga"},
  {"ebu", "Embu"},
  {"ee", "Ewe"},
  {"efi", "Efik"},
  {"egl", "Emilian"},
  {"egy", "Ancient Egyptian"},
  {"eka", "Ekajuk"},
  {"el", "Greek"},
  {"elx", "Elamite"},
  {"en", "English"},
  {"enm", "Middle English"},
  {"eo", "Esperanto"},
  {"es", "Spanish"},
  {"esu", "Central Yupik"},
  {"et", "Estonian"},
  {"eu", "Basque"},
  {"ewo", "Ewondo"},
  {"ext", "Extremaduran"},
  {"fa", "Persian"},
  {"fa-af", "Dari"},
  {"fan", "Fang"},
  {"fat", "Fanti"},
  {"ff", "Fulah"},
  {"fi", "Finnish"},
  {"fil", "Filipino"},
  {"fit", "Tornedalen Finnish"},
  {"fj", "Fijian"},
  {"fo", "Faroese"},
  {"fon", "Fon"},
  {"fr", "French"},
  {"frc", "Cajun French"},
  {"frm", "Middle French"},
  {"fro", "Old French"},
  {"frp", "Arpitan"},
  {"frr", "Northern Frisian"},
  {"frs", "Eastern Frisian"},
  {"fur", "Friulian"},
  {"fy", "Western Frisian"},
  {"ga", "Irish"},
  {"gaa", "Ga"},
  {"gag", "Gagauz"},
  {"gan", "Gan Chinese"},
  {"gay", "Gayo"},
  {"gba", "Gbaya"},
  {"gbz", "Zoroastrian Dari"},
  {"gd", "Scottish Gaelic"},
  {"gez", "Geez"},
  {"gil", "Gilbertese"},
  {"gl", "Galician"},
  {"glk", "Gilaki"},
  {"gmh", "Middle High German"},
  {"gn", "Guarani"},
  {"goh", "Old High German"},
  {"gom", "Goan Konkani"},
  {"gon", "Gondi"},
  {"gor", "Gorontalo"},
  {"got", "Gothic"},
  {"grb", "Grebo"},
  {"grc", "Ancient Greek"},
  {"gsw", "Swiss German"},
  {"gu", "Gujarati"},
  {"guc", "Wayuu"},
  {"gur", "Frafra"},
  {"guz", "Gusii"},
  {"gv", "Manx"},
  {"gwi", "Gwichʼin"},
  {"ha", "Hausa"},
  {"hai", "Haida"},
  {"hak", "Hakka Chinese"},
  {"haw", "Hawaiian"},
  {"he", "Hebrew"},
  {"hi", "Hindi"},
  {"hif", "Fiji Hindi"},
  {"hil", "Hiligaynon"},
  {"hit", "Hittite"},
  {"hmn", "Hmong"},
  {"ho", "Hiri Motu"},
  {"hr", "Croatian"},
  {"hsb", "Upper Sorbian"},
  {"hsn", "Xiang Chinese"},
  {"ht", "Haitian Creole"},
  {"hu", "Hungarian"},
  {"hup", "Hupa"},
  {"hy", "Armenian"},
  {"hz", "Herero"},
  {"ia", "Interlingua"},
  {"iba", "Iban"},
  {"ibb", "Ibibio"},
  {"id", "Indonesian"},
  {"ie", "Interlingue"},
  {"ig", "Igbo"},
  {"ii", "Sichuan Yi"},
  {"ik", "Inupiaq"},
  {"ilo", "Iloko"},
  {"inh", "Ingush"},
  {"io", "Ido"},
  {"is", "Icelandic"},
  {"it", "Italian"},
  {"iu", "Inuktitut"},
  {"izh", "Ingrian"},
  {"ja", "Japanese"},
  {"jam", "Jamaican Creole English"},
  {"jbo", "Lojban"},
  {"jgo", "Ngomba"},
  {"jmc", "Machame"},
  {"jpr", "Judeo-Persian"},
  {"jrb", "Judeo-Arabic"},
  {"jut", "Jutish"},
  {"jv", "Javanese"},
  {"ka", "Georgian"},
  {"kaa", "Kara-Kalpak"},
  {"kab", "Kabyle"},
  {"kac", "Kachin"},
  {"kaj", "Jju"},
  {"kam", "Kamba"},
  {"kaw", "Kawi"},
  {"kbd", "Kabardian"},
  {"kbl", "Kanembu"},
  {"kcg", "Tyap"},
  {"kde", "Makonde"},
  {"kea", "Kabuverdianu"},
  {"ken", "Kenyang"},
  {"kfo", "Koro"},
  {"kg", "Kongo"},
  {"kgp", "Kaingang"},
  {"kha", "Khasi"},
  {"kho", "Khotanese"},
  {"khq", "Koyra Chiini"},
  {"khw", "Khowar"},
  {"ki", "Kikuyu"},
  {"kiu", "Kirmanjki"},
  {"kj", "Kuanyama"},
  {"kk", "Kazakh"},
  {"kkj", "Kako"},
  {"kl", "Kalaallisut"},
  {"kln", "Kalenjin"},
  {"km", "Khmer"},
  {"kmb", "Kimbundu"},
  {"kn", "Kannada"},
  {"ko", "Korean"},
  {"koi", "Komi-Permyak"},
  {"kok", "Konkani"},
  {"kos", "Kosraean"},
  {"kpe", "Kpelle"},
  {"kr", "Kanuri"},
  {"krc", "Karachay-Balkar"},
  {"kri", "Krio"},
  {"krj", "Kinaray-a"},
  {"krl", "Karelian"},
  {"kru", "Kurukh"},
  {"ks", "Kashmiri"},
  {"ksb", "Shambala"},
  {"ksf", "Bafia"},
  {"ksh", "Colognian"},
  {"ku", "Kurdish"},
  {"kum", "Kumyk"},
  {"kut", "Kutenai"},
  {"kv", "Komi"},
  {"kw", "Cornish"},
  {"ky", "Kyrgyz"},
  {"la", "Latin"},
  {"lad", "Ladino"},
  {"lag", "Langi"},
  {"lah", "Lahnda"},
  {"lam", "Lamba"},
  {"lb", "Luxembourgish"},
  {"lez", "Lezghian"},
  {"lfn", "Lingua Franca Nova"},
  {"lg", "Ganda"},
  {"li", "Limburgish"},
  {"lij", "Ligurian"},
  {"liv", "Livonian"},
  {"lkt", "Lakota"},
  {"lmo", "Lombard"},
  {"ln", "Lingala"},
  {"lo", "Lao"},
  {"lol", "Mongo"},
  {"loz", "Lozi"},
  {"lrc", "Northern Luri"},
  {"lt", "Lithuanian"},
  {"ltg", "Latgalian"},
  {"lu", "Luba-Katanga"},
  {"lua", "Luba-Lulua"},
  {"lui", "Luiseno"},
  {"lun", "Lunda"},
  {"luo", "Luo"},
  {"lus", "Mizo"},
  {"luy", "Luyia"},
  {"lv", "Latvian"},
  {"lzh", "Literary Chinese"},
  {"lzz", "Laz"},
  {"mad", "Madurese"},
  {"maf", "Mafa"},
  {"mag", "Magahi"},
  {"mai", "Maithili"},
  {"mak", "Makasar"},
  {"man", "Mandingo"},
  {"mas", "Masai"},
  {"mde", "Maba"},
  {"mdf", "Moksha"},
  {"mdr", "Mandar"},
  {"men", "Mende"},
  {"mer", "Meru"},
  {"mfe", "Morisyen"},
  {"mg", "Malagasy"},
  {"mga", "Middle Irish"},
  {"mgh", "Makhuwa-Meetto"},
  {"mgo", "Metaʼ"},
  {"mh", "Marshallese"},
  {"mi", "Maori"},
  {"mic", "Mi'kmaq"},
  {"min", "Minangkabau"},
  {"mk", "Macedonian"},
  {"ml", "Malayalam"},
  {"mn", "Mongolian"},
  {"mnc", "Manchu"},
  {"mni", "Manipuri"},
  {"moh", "Mohawk"},
  {"mos", "Mossi"},
  {"mr", "Marathi"},
  {"mrj", "Western Mari"},
  {"ms", "Malay"},
  {"mt", "Maltese"},
  {"mua", "Mundang"},
  {"mul", "Multiple languages"},
  {"mus", "Creek"},
  {"mwl", "Mirandese"},
  {"mwr", "Marwari"},
  {"mwv", "Mentawai"},
  {"my", "Burmese"},
  {"mye", "Myene"},
  {"myv", "Erzya"},
  {"mzn", "Mazanderani"},
  {"na", "Nauru"},
  {"nan", "Min Nan Chinese"},
  {"nap", "Neapolitan"},
  {"naq", "Nama"},
  {"nb", "Norwegian Bokmål"},
  {"nd", "North Ndebele"},
  {"nds", "Low German"},
  {"ne", "Nepali"},
  {"new", "Newari"},
  {"ng", "Ndonga"},
  {"nia", "Nias"},
  {"niu", "Niuean"},
  {"njo", "Ao Naga"},
  {"nl", "Dutch"},
  {"nl-be", "Flemish"},
  {"nmg", "Kwasio"},
  {"nn", "Norwegian Nynorsk"},
  {"nnh", "Ngiemboon"},
  {"no", "Norwegian"},
  {"nog", "Nogai"},
  {"non", "Old Norse"},
  {"nov", "Novial"},
  {"nqo", "N’Ko"},
  {"nr", "South Ndebele"},
  {"nso", "Northern Sotho"},
  {"nus", "Nuer"},
  {"nv", "Navajo"},
  {"nwc", "Classical Newari"},
  {"ny", "Nyanja"},
  {"nym", "Nyamwezi"},
  {"nyn", "Nyankole"},
  {"nyo", "Nyoro"},
  {"nzi", "Nzima"},
  {"oc", "Occitan"},
  {"oj", "Ojibwa"},
  {"om", "Oromo"},
  {"or", "Odia"},
  {"os", "Ossetic"},
  {"osa", "Osage"},
  {"ota", "Ottoman Turkish"},
  {"pa", "Punjabi"},
  {"pag", "Pangasinan"},
  {"pal", "Pahlavi"},
  {"pam", "Pampanga"},
  {"pap", "Papiamento"},
  {"pau", "Palauan"},
  {"pcd", "Picard"},
  {"pcm", "Nigerian Pidgin"},
  {"pdc", "Pennsylvania German"},
  {"pdt", "Plautdietsch"},
  {"peo", "Old Persian"},
  {"pfl", "Palatine German"},
  {"phn", "Phoenician"},
  {"pi", "Pali"},
  {"pl", "Polish"},
  {"pms", "Piedmontese"},
  {"pnt", "Pontic"},
  {"pon", "Pohnpeian"},
  {"prg", "Prussian"},
  {"pro", "Old Provençal"},
  {"ps", "Pashto"},
  {"pt", "Portuguese"},
  {"qu", "Quechua"},
  {"quc", "Kʼicheʼ"},
  {"qug", "Chimborazo Highland Quichua"},
  {"raj", "Rajasthani"},
  {"rap", "Rapanui"},
  {"rar", "Rarotongan"},
  {"rgn", "Romagnol"},
  {"rif", "Riffian"},
  {"rm", "Romansh"},
  {"rn", "Rundi"},
  {"ro", "Romanian"},
  {"ro-md", "Moldavian"},
  {"rof", "Rombo"},
  {"rom", "Romany"},
  {"root", "Root"},
  {"rtm", "Rotuman"},
  {"ru", "Russian"},
  {"rue", "Rusyn"},
  {"rug", "Roviana"},
  {"rup", "Aromanian"},
  {"rw", "Kinyarwanda"},
  {"rwk", "Rwa"},
  {"sa", "Sanskrit"},
  {"sad", "Sandawe"},
  {"sah", "Sakha"},
  {"sam", "Samaritan Aramaic"},
  {"saq", "Samburu"},
  {"sas", "Sasak"},
  {"sat", "Santali"},
  {"saz", "Saurashtra"},
  {"sba", "Ngambay"},
  {"sbp", "Sangu"},
  {"sc", "Sardinian"},
  {"scn", "Sicilian"},
  {"sco", "Scots"},
  {"sd", "Sindhi"},
  {"sdc", "Sassarese Sardinian"},
  {"sdh", "Southern Kurdish"},
  {"se", "Northern Sami"},
  {"see", "Seneca"},
  {"seh", "Sena"},
  {"sei", "Seri"},
  {"sel", "Selkup"},
  {"ses", "Koyraboro Senni"},
  {"sg", "Sango"},
  {"sga", "Old Irish"},
  {"sgs", "Samogitian"},
  {"sh", "Serbo-Croatian"},
  {"shi", "Tachelhit"},
  {"shn", "Shan"},
  {"shu", "Chadian Arabic"},
  {"si", "Sinhala"},
  {"sid", "Sidamo"},
  {"sk", "Slovak"},
  {"sl", "Slovenian"},
  {"sli", "Lower Silesian"},
  {"sly", "Selayar"},
  {"sm", "Samoan"},
  {"sma", "Southern Sami"},
  {"smj", "Lule Sami"},
  {"smn", "Inari Sami"},
  {"sms", "Skolt Sami"},
  {"sn", "Shona"},
  {"snk", "Soninke"},
  {"so", "Somali"},
  {"sog", "Sogdien"},
  {"sq", "Albanian"},
  {"sr", "Serbian"},
  {"srn", "Sranan Tongo"},
  {"srr", "Serer"},
  {"ss", "Swati"},
  {"ssy", "Saho"},
  {"st", "Southern Sotho"},
  {"stq", "Saterland Frisian"},
  {"su", "Sundanese"},
  {"suk", "Sukuma"},
  {"sus", "Susu"},
  {"sux", "Sumerian"},
  {"sv", "Swedish"},
  {"sw", "Swahili"},
  {"swb", "Comorian"},
  {"syc", "Classical Syriac"},
  {"syr", "Syriac"},
  {"szl", "Silesian"},
  {"ta", "Tamil"},
  {"tcy", "Tulu"},
  {"te", "Telugu"},
  {"tem", "Timne"},
  {"teo", "Teso"},
  {"ter", "Tereno"},
  {"tet", "Tetum"},
  {"tg", "Tajik"},
  {"th", "Thai"},
  {"ti", "Tigrinya"},
  {"tig", "Tigre"},
  {"tiv", "Tiv"},
  {"tk", "Turkmen"},
  {"tkl", "Tokelau"},
  {"tkr", "Tsakhur"},
  {"tl", "Tagalog"},
  {"tlh", "Klingon"},
  {"tli", "Tlingit"},
  {"tly", "Talysh"},
  {"tmh", "Tamashek"},
  {"tn", "Tswana"},
  {"to", "Tongan"},
  {"tog", "Nyasa Tonga"},
  {"tpi", "Tok Pisin"},
  {"tr", "Turkish"},
  {"tru", "Turoyo"},
  {"trv", "Taroko"},
  {"ts", "Tsonga"},
  {"tsd", "Tsakonian"},
  {"tsi", "Tsimshian"},
  {"tt", "Tatar"},
  {"ttt", "Muslim Tat"},
  {"tum", "Tumbuka"},
  {"tvl", "Tuvalu"},
  {"tw", "Twi"},
  {"twq", "Tasawaq"},
  {"ty", "Tahitian"},
  {"tyv", "Tuvinian"},
  {"tzm", "Central Atlas Tamazight"},
  {"udm", "Udmurt"},
  {"ug", "Uyghur"},
  {"uga", "Ugaritic"},
  {"uk", "Ukrainian"},
  {"umb", "Umbundu"},
  {"und", "Unknown language"},
  {"ur", "Urdu"},
  {"uz", "Uzbek"},
  {"vai", "Vai"},
  {"ve", "Venda"},
  {"vec", "Venetian"},
  {"vep", "Veps"},
  {"vi", "Vietnamese"},
  {"vls", "West Flemish"},
  {"vmf", "Main-Franconian"},
  {"vo", "Volapük"},
  {"vot", "Votic"},
  {"vro", "Võro"},
  {"vun", "Vunjo"},
  {"wa", "Walloon"},
  {"wae", "Walser"},
  {"wal", "Wolaytta"},
  {"war", "Waray"},
  {"was", "Washo"},
  {"wbp", "Warlpiri"},
  {"wo", "Wolof"},
  {"wuu", "Wu Chinese"},
  {"xal", "Kalmyk"},
  {"xh", "Xhosa"},
  {"xmf", "Mingrelian"},
  {"xog", "Soga"},
  {"yao", "Yao"},
  {"yap", "Yapese"},
  {"yav", "Yangben"},
  {"ybb", "Yemba"},
  {"yi", "Yiddish"},
  {"yo", "Yoruba"},
  {"yrl", "Nheengatu"},
  {"yue", "Cantonese"},
  {"za", "Zhuang"},
  {"zap", "Zapotec"},
  {"zbl", "Blissymbols"},
  {"zea", "Zeelandic"},
  {"zen", "Zenaga"},
  {"zgh", "Standard Moroccan Tamazight"},
  {"zh", "Chinese"},
  {"zh-hans", "Chinese (Simplified)"},
  {"zh-hant", "Chinese (Traditional)"},
  {"zh-hk", "Chinese (Hong Kong)"},
  {"zu", "Zulu"},
  {"zun", "Zuni"},
  {"zxx", "No linguistic content"},
  {"zza", "Zaza"},
};

void MyFrame::RebuildLanguageChoice() {
  const std::set<std::string>& langs =
    textSettings_->GetSupportedTextLanguages();

  languageChoice_->Clear();
  if (langs.empty()) {
    languageChoice_->Hide();
    return;
  }

  languageChoice_->Append(std::string("Other language"));
  languageChoice_->SetSelection(0);

  if (langs.size() > 1) {
    // TODO: It would be nice to add a separator to the menu choice,
    // so that "Other language" is visually separated from the list of
    // language names for which the font has special lookups.
    // However, wxWidgets does not support separators inside wxChoice
    // (as of August 2016).
  }

  const std::string& curLang = textSettings_->GetTextLanguage();
  for (const std::string& lang : langs) {
    wxString label(lang);
    void* data = static_cast<void*>(const_cast<std::string*>(&lang));
    auto iter = languageNames.find(lang);
    if (iter != languageNames.end()) {
      label.assign(iter->second);
    }
    languageChoice_->Append(label, data);
    if (lang.compare(curLang) == 0) {
      languageChoice_->SetSelection(
          static_cast<int>(languageChoice_->GetCount()) - 1);
    }
  }
  languageChoice_->Show();
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

void MyFrame::OnLanguageChoiceChanged(wxCommandEvent& event) {
  if (!processingModelChange_) {
    const std::string* lang =
        static_cast<const std::string*>(event.GetClientData());
    textSettings_->SetTextLanguage(lang ? *lang : "und");
  }
}

void MyFrame::OnAxisSliderChanged(wxCommandEvent& event) {
  FontStyle::Variation var;
  for (const AxisSlider& s : axisSliders_) {
    double range = s.axis->GetMaxValue() - s.axis->GetMinValue();
    double fraction = static_cast<double>(s.slider->GetValue()) / 1000;
    double value = s.axis->GetMinValue() + fraction * range;
    var[s.axis->GetTag()] = value;
  }
  textSettings_->SetVariation(var);
}

void MyFrame::OnFontSizeFieldChanged(wxSpinDoubleEvent& event) {
  textSettings_->SetFontSize(event.GetValue());
}

wxIMPLEMENT_APP(MyApp);
