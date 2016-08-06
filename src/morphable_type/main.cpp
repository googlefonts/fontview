#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif  // WX_PRECOMP

#include <stdio.h>

class MyApp : public wxApp {
 public:
  virtual bool OnInit();
};

class MyFrame : public wxFrame {
 public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

 private:
  void OnHello(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  wxDECLARE_EVENT_TABLE();
};

enum {
  ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello,   MyFrame::OnHello)
EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

bool MyApp::OnInit() {
  MyFrame* frame =
    new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
  frame->Show(true);
  return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos,
		 const wxSize& size)
  : wxFrame(NULL, wxID_ANY, title, pos, size) {
  wxMenu* fileMenu = new wxMenu();
  fileMenu->Append(ID_Hello, "&Hello...\tCtrl-H",
		   "Help string shown in status bar for this menu item");
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_EXIT);
  wxMenu* helpMenu = new wxMenu();
  helpMenu->Append(wxID_ABOUT);
  wxMenuBar* menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, "&File");
  menuBar->Append(helpMenu, "&Help");
  SetMenuBar(menuBar);
}

void MyFrame::OnExit(wxCommandEvent& event) {
  Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
  wxMessageBox( "This is a wxWidgets Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event) {
  wxLogMessage("Hello world from wxWidgets!");
}

wxIMPLEMENT_APP(MyApp);
