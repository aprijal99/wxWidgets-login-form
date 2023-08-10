#pragma once

#include <wx/wx.h>

class Frame: public wxFrame
{
public:
  Frame(wxWindow* parent, const wxString& title);

private:
  wxTextCtrl* emailField, * passwordField;

  void SetupForm();
};