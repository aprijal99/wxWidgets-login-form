#include "App.hpp"
#include "Frame.hpp"
#include "LoginDialog.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
  wxInitAllImageHandlers();

  LoginDialog loginDialog(nullptr, "Login");
  if (loginDialog.ShowModal() != wxID_OK)
  {
    loginDialog.Destroy();
    return false;
  }
  loginDialog.Destroy();

  Frame* frame = new Frame(nullptr, "My Application");
  frame->Show(true);

  return true;
}
