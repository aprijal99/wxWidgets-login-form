package org.ghiyas.company.backend.service;

import org.ghiyas.company.backend.entity.AccountEntity;
import org.ghiyas.company.backend.repository.AccountRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@Transactional
public class AccountServiceImpl implements AccountService {
    private final AccountRepository accountRepository;

    public AccountServiceImpl(AccountRepository accountRepository) {
        this.accountRepository = accountRepository;
    }

    @Override
    public void saveAccount(AccountEntity accountEntity) {
        accountRepository.save(accountEntity);
    }

    @Override
    public AccountEntity getAccountByEmail(String email) {
        return accountRepository.getAccountEntityByEmail(email).orElse(null);
    }
}
