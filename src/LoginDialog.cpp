#include "LoginDialog.hpp"

LoginDialog::LoginDialog(wxWindow* parent, const wxString& title)
  : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
  // Login form layout
  wxPanel* topPanel = new wxPanel(this, wxID_ANY);
  topPanel->SetBackgroundColour(wxColour("white"));
  wxBoxSizer* topPanelSizer = new wxBoxSizer(wxHORIZONTAL);

  wxPanel* centeringPanel = new wxPanel(topPanel, wxID_ANY);
  wxBoxSizer* centeringSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* formSizer = new wxBoxSizer(wxHORIZONTAL);
  wxFlexGridSizer* fgs = new wxFlexGridSizer(2, 2, 10, 10);

  wxStaticText* emailLabel = new wxStaticText(centeringPanel, wxID_ANY, "Email");
  emailField = new wxTextCtrl(centeringPanel, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(250), FromDIP(23)));
  wxStaticText* passwordLabel = new wxStaticText(centeringPanel, wxID_ANY, "Password");
  passwordField = new wxTextCtrl(centeringPanel, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(250), FromDIP(23)), wxTE_PASSWORD);

  fgs->Add(emailLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
  fgs->Add(emailField, 1, wxEXPAND);
  fgs->Add(passwordLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
  fgs->Add(passwordField, 1, wxEXPAND);

  formSizer->Add(fgs);
  centeringPanel->SetSizer(formSizer);
  centeringSizer->Add(centeringPanel, 0, wxALIGN_CENTER);
  topPanelSizer->Add(centeringSizer, 1, wxALIGN_CENTER);
  topPanel->SetSizerAndFit(topPanelSizer);

  // Buttons layout
  wxPanel* buttonPanel = new wxPanel(this, wxID_ANY);
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

  wxPanel* borderPanel = new wxPanel(this, wxID_ANY);
  borderPanel->SetBackgroundColour(wxColour("gray"));

  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(topPanel, 1, wxEXPAND);
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