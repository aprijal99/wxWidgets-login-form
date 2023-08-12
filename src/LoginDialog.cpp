#include "LoginDialog.hpp"

LoginDialog::LoginDialog(wxWindow* parent, const wxString& title)
  : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
  wxPanel* loginFormPanel = new wxPanel(this);
  loginFormPanel->SetBackgroundColour(wxColour("white"));

  wxPanel* buttonPanel = new wxPanel(this);
  wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

  wxButton* registerButton = new wxButton(buttonPanel, wxID_ANY, "Register");
  registerButton->DisableFocusFromKeyboard();
  wxButton* loginButton = new wxButton(buttonPanel, wxID_ANY, "Login");
  loginButton->DisableFocusFromKeyboard();
  loginButton->Disable();

  buttonSizer->Add(registerButton, 0, wxALL, FromDIP(10));
  buttonSizer->AddStretchSpacer(1);
  buttonSizer->Add(loginButton, 0, wxALL, FromDIP(10));
  buttonPanel->SetSizer(buttonSizer);

  wxPanel* borderPanel = new wxPanel(this);
  borderPanel->SetBackgroundColour(wxColour("gray"));

  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(loginFormPanel, 1, wxEXPAND);
  mainSizer->Add(borderPanel, 0, wxEXPAND);
  mainSizer->Add(buttonPanel, 0, wxEXPAND);

  this->SetSizer(mainSizer);
  this->SetIcon(wxIcon("logo.png", wxBITMAP_TYPE_PNG));
  this->SetSize(wxSize(FromDIP(650), FromDIP(550)));
  this->Centre();
}

void LoginDialog::OnClose(wxCloseEvent& event)
{
  this->EndModal(wxID_CANCEL);
}

BEGIN_EVENT_TABLE(LoginDialog, wxDialog)
  EVT_CLOSE(LoginDialog::OnClose)
END_EVENT_TABLE()