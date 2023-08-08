package org.ghiyas.company.backend.service;

import org.ghiyas.company.backend.entity.AccountEntity;

public interface AccountService {
    void saveAccount(AccountEntity accountEntity);
    AccountEntity getAccountByEmail(String email);
}
