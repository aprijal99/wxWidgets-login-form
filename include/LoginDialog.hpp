#pragma once

#include <wx/wx.h>
#include <wx/webrequest.h>
#include "JwtUtil.hpp"

class LoginDialog: public wxDialog
{
public:
  LoginDialog(wxWindow* parent, const wxString& title);
  wxSecretValue GetSecretToken();

private:
  wxTextCtrl* emailField, * passwordField;
  wxSecretValue secretToken;

  wxPanel* SetupTopPanel();
  wxPanel* SetupButtonPanel();

  void OnClose(wxCloseEvent& event);
  void OnClickLoginButton(wxCommandEvent& event);
  void OnLoginResponse(wxWebRequestEvent& event);
  wxDECLARE_EVENT_TABLE();
};