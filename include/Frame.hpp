#pragma once

#include <wx/wx.h>

class Frame: public wxFrame
{
public:
  Frame(wxWindow* parent, const wxString& title);
  ~Frame()
  {
    wxLog::SetActiveTarget(nullptr);
    delete logger;
  }

private:
  wxTextCtrl* emailField, * passwordField;
  wxLog* logger;

  void SetupForm();
};