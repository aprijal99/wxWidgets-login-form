#pragma once

#include <wx/wx.h>

class LoginDialog: public wxDialog
{
public:
  LoginDialog(wxWindow* parent, const wxString& title);
};