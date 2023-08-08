#include <vector>
#include "Frame.hpp"

Frame::Frame(wxWindow* parent, const wxString& title)
  : wxFrame(parent, wxID_ANY, title)
{
  SetupForm();
}

void Frame::SetupForm()
{
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* centeringSizer = new wxBoxSizer(wxHORIZONTAL);

  wxPanel* panel = new wxPanel(this);
  wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText* emailLabel = new wxStaticText(panel, wxID_ANY, "Email:");
  emailField = new wxTextCtrl(panel, wxID_ANY);

  wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password:");
  passwordField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

  wxButton* submitButton = new wxButton(panel, wxID_ANY, "Submit");
  submitButton->SetCursor(wxCursor(wxCURSOR_HAND));

  std::vector<wxWindow*> formItems { emailLabel, emailField, passwordLabel, passwordField, submitButton };

  for (wxWindow* item: formItems)
  {
    panelSizer->Add(item, 0, wxEXPAND | wxALL, FromDIP(3));
  }

  panel->SetSizerAndFit(panelSizer);

  centeringSizer->Add(panel, 1, wxALIGN_CENTER | wxALL, FromDIP(10));
  sizer->Add(centeringSizer, 1, wxEXPAND);

  this->SetSizerAndFit(sizer);
  this->SetBackgroundColour(panel->GetBackgroundColour());
  this->SetMinSize(wxSize(FromDIP(300), wxDefaultSize.GetHeight()));
}