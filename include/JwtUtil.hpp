#pragma once

#include <wx/wx.h>
#include <wx/secretstore.h>

class JwtUtil
{
public:
  static bool SaveToken(const wxString& tokenName, const wxString& token);
  static bool LoadToken(wxSecretValue& secretToken);
  static bool DeleteToken();

private:
  static wxString service;
};