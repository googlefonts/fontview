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
#include FT_GLYPH_H
#include FT_MULTIPLE_MASTERS_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H


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
  std::vector<std::map<int, std::string>> faceNames_;
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

static const wxFontEncoding UNSUPPORTED_ENCODING =
    static_cast<wxFontEncoding>(-1);

wxFontEncoding GetFontNameEncoding(const FT_SfntName& name) {
  if (name.platform_id == TT_PLATFORM_MICROSOFT) {
    switch (name.encoding_id) {
    case TT_MS_ID_UNICODE_CS: return wxFONTENCODING_UTF16BE;
    case TT_MS_ID_SJIS: return wxFONTENCODING_SHIFT_JIS;
    case TT_MS_ID_GB2312: return wxFONTENCODING_GB2312;
    case TT_MS_ID_BIG_5: return wxFONTENCODING_BIG5;
    case TT_MS_ID_JOHAB: return wxFONTENCODING_JOHAB;
    default: break;
    }
  }

  if (name.platform_id == TT_PLATFORM_APPLE_UNICODE) {
    return wxFONTENCODING_UTF16BE;
  }

  if (name.platform_id == TT_PLATFORM_MACINTOSH) {
    switch (name.encoding_id) {
    case TT_MAC_ID_ROMAN: return wxFONTENCODING_MACROMAN;
    case TT_MAC_ID_JAPANESE: return wxFONTENCODING_MACJAPANESE;
    case TT_MAC_ID_TRADITIONAL_CHINESE: return wxFONTENCODING_MACCHINESETRAD;
    case TT_MAC_ID_KOREAN: return wxFONTENCODING_MACKOREAN;
    case TT_MAC_ID_ARABIC: return wxFONTENCODING_MACARABIC;
    case TT_MAC_ID_HEBREW: return wxFONTENCODING_MACHEBREW;
    case TT_MAC_ID_GREEK: return wxFONTENCODING_MACGREEK;
    case TT_MAC_ID_RUSSIAN: return wxFONTENCODING_MACCYRILLIC;
    case TT_MAC_ID_DEVANAGARI: return wxFONTENCODING_MACDEVANAGARI;
    case TT_MAC_ID_GURMUKHI: return wxFONTENCODING_MACGURMUKHI;
    case TT_MAC_ID_GUJARATI: return wxFONTENCODING_MACGUJARATI;
    case TT_MAC_ID_ORIYA: return wxFONTENCODING_MACORIYA;
    case TT_MAC_ID_BENGALI: return wxFONTENCODING_MACBENGALI;
    case TT_MAC_ID_TAMIL: return wxFONTENCODING_MACTAMIL;
    case TT_MAC_ID_TELUGU: return wxFONTENCODING_MACTELUGU;
    case TT_MAC_ID_KANNADA: return wxFONTENCODING_MACKANNADA;
    case TT_MAC_ID_MALAYALAM: return wxFONTENCODING_MACMALAJALAM;
    case TT_MAC_ID_SINHALESE: return wxFONTENCODING_MACSINHALESE;
    case TT_MAC_ID_BURMESE: return wxFONTENCODING_MACBURMESE;
    case TT_MAC_ID_KHMER: return wxFONTENCODING_MACKHMER;
    case TT_MAC_ID_THAI: return wxFONTENCODING_MACTHAI;
    case TT_MAC_ID_LAOTIAN: return wxFONTENCODING_MACLAOTIAN;
    case TT_MAC_ID_GEORGIAN: return wxFONTENCODING_MACGEORGIAN;
    case TT_MAC_ID_ARMENIAN: return wxFONTENCODING_MACARMENIAN;
    case TT_MAC_ID_SIMPLIFIED_CHINESE: return wxFONTENCODING_MACCHINESESIMP;
    case TT_MAC_ID_TIBETAN: return wxFONTENCODING_MACTIBETAN;
    case TT_MAC_ID_MONGOLIAN: return wxFONTENCODING_MACMONGOLIAN;
    case TT_MAC_ID_GEEZ: return wxFONTENCODING_MACETHIOPIC;
    case TT_MAC_ID_SLAVIC: return wxFONTENCODING_MACCENTRALEUR;
    case TT_MAC_ID_VIETNAMESE: return wxFONTENCODING_MACVIATNAMESE;
    default: break;
    }
  }

  return UNSUPPORTED_ENCODING;
}


int GetFontNameQuality(const FT_SfntName& name) {
  const wxFontEncoding encoding = GetFontNameEncoding(name);
  if (encoding == UNSUPPORTED_ENCODING) {
    return 0;
  }

  wxCSConv converter(encoding);
  if (!converter.IsOk()) {
    return 0;
  }

  // Give a slight preference to Unicode-encoded names.
  int encodingQuality = 0;
  if (encoding == wxFONTENCODING_UTF16BE) {
    encodingQuality = 2;
  }

  // TODO: Run a language matcher against the user's preferred languages.
  // Currently, we prefer US English and penalize everything else.
  if (name.platform_id == TT_PLATFORM_MICROSOFT) {
    encodingQuality += name.language_id == 1033 ? 10 : 5;
    return encodingQuality;
  }

  if (name.platform_id == TT_PLATFORM_MACINTOSH) {
    encodingQuality += name.language_id == 0 ? 10 : 5;
    return encodingQuality;
  }

  return 0;
}

void GetFontNames(FT_Face face, std::map<int, std::string>* names) {
  const FT_UInt numNames = FT_Get_Sfnt_Name_Count(face);
  std::map<int, int> nameQuality;
  FT_SfntName name;
  for (FT_UInt i = 0; i < numNames; ++i) {
    if (FT_Get_Sfnt_Name(face, i, &name) != 0) {
      continue;
    }

    int curQuality = GetFontNameQuality(name);
    if (curQuality == 0) {
      continue;
    }

    int bestQuality = nameQuality[name.name_id];
    if (curQuality < bestQuality) {
      continue;
    }

    const wxFontEncoding encoding = GetFontNameEncoding(name);
    if (encoding == UNSUPPORTED_ENCODING) {
      continue;
    }

    wxCSConv converter(encoding);
    if (!converter.IsOk()) {
      continue;
    }

    wxString convertedName(name.string, converter, name.string_len);
    nameQuality[name.name_id] = curQuality;
    (*names)[name.name_id] = convertedName.ToStdString();
  }
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
    faces_(faces), faceNames_(faces->size()),
    familyChoice_(NULL), styleChoice_(NULL), sizeControl_(NULL) {
  for (size_t i = 0; i < faces->size(); ++i) {
    GetFontNames(faces->at(i), &faceNames_[i]);
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
  for (FT_Face face : *faces_) {
    if (face->family_name) {
      families.insert(face->family_name);
      if (firstFamily.empty()) {
	firstFamily.assign(face->family_name);
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
  for (size_t faceIndex = 0; faceIndex < faces_->size(); ++faceIndex) {
    FT_Face face = faces_->at(faceIndex);
    std::map<int, std::string>& names = faceNames_[faceIndex];
    if (family != face->family_name) {
      continue;
    }
    FT_MM_Var* variations = NULL;
    if (FT_HAS_MULTIPLE_MASTERS(face)) {
      FT_Get_MM_Var(face, &variations);
    }
    if (variations && variations->num_namedstyles > 0) {
      for (FT_UInt i = 0; i < variations->num_namedstyles; ++i) {
	std::string styleName = names[variations->namedstyle[i].strid];
	styleChoice_->Append(styleName);
      }
    } else {
      styleChoice_->Append(face->style_name);
    }
  }
}

wxIMPLEMENT_APP(MyApp);
