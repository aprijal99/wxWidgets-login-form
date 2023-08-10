#include <wx/webrequest.h>
#include <vector>
#include <iostream>
#include <string>
#include "json.hpp"
#include "Frame.hpp"
#include "LoginDialog.hpp"

Frame::Frame(wxWindow* parent, const wxString& title)
  : wxFrame(parent, wxID_ANY, title)
{
  SetupForm();

  this->Centre();
}

void Frame::SetupForm()
{
  // LoginDialog loginDialog(this, "Login");
  // loginDialog.ShowModal();

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
  submitButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(
      this,
      "https://dummyjson.com/products/add"
    );
    request.SetMethod("POST");

    nlohmann::json data = nlohmann::json({{"title", "Pencil"}});
    request.SetData("{\"title\": \"Pencil\"}", "application/json");

    if (request.IsOk()) request.Start();
    else wxLogWarning("Failed to create the request");
  });

  this->Bind(wxEVT_WEBREQUEST_STATE, [](wxWebRequestEvent& event) {
    switch (event.GetState())
    {
      case wxWebRequest::State_Completed:
      {
        wxLogInfo("Get request executed successfully");

        wxWebResponse response = event.GetResponse();
        wxLogInfo(response.AsString());
        // auto productsJson = nlohmann::json::parse(response.AsString());

        // for (auto& obj: productsJson["products"])
        // {
        //   std::string title = obj["title"];
        //   wxLogInfo("%s", title);
        // }

        break;
      }
      case wxWebRequest::State_Failed:
        wxLogWarning("Get request failed");
        break;
    }
  });

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