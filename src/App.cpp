#include "App.hpp"
#include "Frame.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
  Frame* frame = new Frame(nullptr, "Login Form");
  frame->Show(true);

  return true;
}