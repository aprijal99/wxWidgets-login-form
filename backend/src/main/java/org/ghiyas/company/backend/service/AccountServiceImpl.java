package org.ghiyas.company.backend.service;

import org.ghiyas.company.backend.entity.AccountEntity;
import org.ghiyas.company.backend.repository.AccountRepository;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.UUID;

@Service
@Transactional
public class AccountServiceImpl implements AccountService, UserDetailsService {
    private final AccountRepository accountRepository;
    private final PasswordEncoder passwordEncoder;

    public AccountServiceImpl(AccountRepository accountRepository, PasswordEncoder passwordEncoder) {
        this.accountRepository = accountRepository;
        this.passwordEncoder = passwordEncoder;
    }

    @Override
    public void saveAccount(AccountEntity accountEntity) {
        accountEntity.setId(UUID.randomUUID().toString());
        accountEntity.setPassword(passwordEncoder.encode(accountEntity.getPassword()));
        accountEntity.setRole("USER");

        accountRepository.save(accountEntity);
    }

    @Override
    public AccountEntity findAccountByEmail(String email) {
        return accountRepository.findAccountEntityByEmail(email).orElse(null);
    }

    @Override
    public UserDetails loadUserByUsername(String email) throws UsernameNotFoundException {
        AccountEntity accountEntity = this.findAccountByEmail(email);
        List<SimpleGrantedAuthority> authorities = List.of(
                new SimpleGrantedAuthority(accountEntity.getRole())
        );

        return new User(
                accountEntity.getEmail(),
                accountEntity.getPassword(),
                authorities
        );
    }
}
