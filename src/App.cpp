#include "App.hpp"
#include "Frame.hpp"
#include "LoginDialog.hpp"
#include "JwtUtil.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
  wxInitAllImageHandlers();

  wxSecretValue secretToken;
  if (!JwtUtil::LoadToken(secretToken))
  {
    LoginDialog loginDialog(nullptr, "Welcome to Student Management Control");
    if (loginDialog.ShowModal() != wxID_OK)
    {
      loginDialog.Destroy();
      return false;
    }

    loginDialog.Destroy();
  }

  Frame* frame = new Frame(nullptr, "My Application");
  frame->Show(true);

  return true;
}
