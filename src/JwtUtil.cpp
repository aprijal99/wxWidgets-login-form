#include "JwtUtil.hpp"

wxString JwtUtil::service = "JWT/ACCESS_TOKEN";

bool JwtUtil::SaveToken(const wxString& tokenName, const wxString& token)
{
  wxSecretStore store = wxSecretStore::GetDefault();
  if (!store.IsOk()) return false;

  return store.Save(service, tokenName, wxSecretValue(token));
}

bool JwtUtil::LoadToken(wxSecretValue& secretToken)
{
  wxSecretStore store = wxSecretStore::GetDefault();
  if (!store.IsOk()) return false;

  wxString tokenName;
  return store.Load(service, tokenName, secretToken);
}

bool JwtUtil::DeleteToken()
{
  wxSecretStore store = wxSecretStore::GetDefault();
  if (!store.IsOk()) return false;

  return store.Delete(service);
}