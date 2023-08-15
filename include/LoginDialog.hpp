#pragma once

#include <wx/wx.h>
#include <wx/webrequest.h>

class LoginDialog: public wxDialog
{
public:
  LoginDialog(wxWindow* parent, const wxString& title);

private:
  wxTextCtrl* emailField, * passwordField;

  wxPanel* SetupTopPanel();
  wxPanel* SetupButtonPanel();

  void OnClose(wxCloseEvent& event);
  void OnClickLoginButton(wxCommandEvent& event);
  void OnLoginResponse(wxWebRequestEvent& event);
  wxDECLARE_EVENT_TABLE();
};