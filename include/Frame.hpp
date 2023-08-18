#pragma once

#include <wx/wx.h>
#include "JwtUtil.hpp"

class Frame: public wxFrame
{
public:
  Frame(wxWindow* parent, const wxString& title);
};