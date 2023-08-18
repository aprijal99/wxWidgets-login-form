#include "Frame.hpp"

Frame::Frame(wxWindow* parent, const wxString& title)
  : wxFrame(parent, wxID_ANY, title)
{
  wxPanel* framePanel = new wxPanel(this, wxID_ANY);
  framePanel->SetBackgroundColour(wxColour("white"));

  wxMenu* fileMenu = new wxMenu();
  this->Bind(
    wxEVT_MENU,
    [this](wxCommandEvent& event) {
      JwtUtil::DeleteToken();
      this->Close();
    },
    fileMenu->Append(wxID_ANY, wxT("Sign Out"))->GetId()
  );

	wxMenuBar* menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, wxT("&File"));

	this->SetMenuBar(menuBar);
  this->SetSize(wxSize(FromDIP(1400), FromDIP(800)));
  this->Centre();
}