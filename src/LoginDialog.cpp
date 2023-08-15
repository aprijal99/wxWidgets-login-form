#include <string>
#include "LoginDialog.hpp"
#include "json.hpp"

LoginDialog::LoginDialog(wxWindow* parent, const wxString& title)
  : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
  this->Bind(wxEVT_WEBREQUEST_STATE, &LoginDialog::OnLoginResponse, this);

  // Top panel
  wxPanel* topPanel = SetupTopPanel();

  // Button panel
  wxPanel* buttonPanel = SetupButtonPanel();

  // Border
  wxPanel* borderPanel = new wxPanel(this, wxID_ANY);
  borderPanel->SetBackgroundColour(wxColour("gray"));

  // Main sizer
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(topPanel, 1, wxEXPAND);
  mainSizer->Add(borderPanel, 0, wxEXPAND);
  mainSizer->Add(buttonPanel, 0, wxEXPAND);

  // Set main sizer to LoginDialog
  this->SetSizer(mainSizer);
  this->SetIcon(wxIcon("logo.png", wxBITMAP_TYPE_PNG));
  this->SetSize(wxSize(FromDIP(650), FromDIP(550)));
  this->Centre();
}

wxPanel* LoginDialog::SetupTopPanel()
{
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

  return topPanel;
}

wxPanel* LoginDialog::SetupButtonPanel()
{
  wxPanel* buttonPanel = new wxPanel(this, wxID_ANY);
  wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

  wxButton* registerButton = new wxButton(buttonPanel, wxID_ANY, "Register");
  registerButton->DisableFocusFromKeyboard();
  wxButton* loginButton = new wxButton(buttonPanel, wxID_ANY, "Login");
  loginButton->Bind(wxEVT_BUTTON, &LoginDialog::OnClickLoginButton, this);
  loginButton->DisableFocusFromKeyboard();
  // loginButton->Disable();

  buttonSizer->Add(registerButton, 0, wxALL, FromDIP(10));
  buttonSizer->AddStretchSpacer(1);
  buttonSizer->Add(loginButton, 0, wxALL, FromDIP(10));
  buttonPanel->SetSizer(buttonSizer);

  return buttonPanel;
}

void LoginDialog::OnClose(wxCloseEvent& event)
{
  this->EndModal(wxID_CANCEL);
}

void LoginDialog::OnClickLoginButton(wxCommandEvent& event)
{
  wxString email = emailField->GetLineText(0);
  email.Replace("@", "%40");
  wxString password = passwordField->GetLineText(0);

  wxString encodedEmailPassword = wxString("email=")
    .Append(email)
    .Append("&")
    .Append("password=")
    .Append(password);

  wxWebRequest request = wxWebSession::GetDefault().CreateRequest(
    this,
    "http://localhost:8050/login"
  );
  request.SetMethod("POST");
  request.SetData(encodedEmailPassword, "application/x-www-form-urlencoded");

  if (request.IsOk()) request.Start();
  else wxLogWarning("Failed to create the request");
}

void LoginDialog::OnLoginResponse(wxWebRequestEvent& event)
{
  switch (event.GetState())
  {
    case wxWebRequest::State_Completed:
    {
      wxWebResponse response = event.GetResponse();
      auto responseJson = nlohmann::json::parse(response.AsString());
      std::string token = responseJson["data"]["access_token"];

      wxLogInfo("%s", token);

      break;
    }
    case wxWebRequest::State_Failed:
      wxLogWarning("Get request failed");
      break;
  }
}

BEGIN_EVENT_TABLE(LoginDialog, wxDialog)
  EVT_CLOSE(LoginDialog::OnClose)
END_EVENT_TABLE()