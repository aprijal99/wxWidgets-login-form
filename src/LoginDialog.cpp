#include "LoginDialog.hpp"

LoginDialog::LoginDialog(wxWindow* parent, const wxString& title)
  : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
  wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(buttonSizer, 0);

  this->SetSizer(sizer);
  this->Centre();
  this->SetIcon(wxIcon("logo.png", wxBITMAP_TYPE_PNG));
}