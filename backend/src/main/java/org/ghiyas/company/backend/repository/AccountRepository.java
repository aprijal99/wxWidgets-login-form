package org.ghiyas.company.backend.repository;

import org.ghiyas.company.backend.entity.AccountEntity;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface AccountRepository extends JpaRepository<AccountEntity, String> {
    Optional<AccountEntity> getAccountEntityByEmail(String email);
}
