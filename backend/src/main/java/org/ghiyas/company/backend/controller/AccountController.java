package org.ghiyas.company.backend.controller;

import org.ghiyas.company.backend.service.AccountService;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping(path = "/account")
public class AccountController {
    private final AccountService accountService;

    public AccountController(AccountService accountService) {
        this.accountService = accountService;
    }

    @GetMapping(produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<?> getOne() {
        return ResponseEntity.ok()
                .body(Map.of(
                        "name", "Aprijal Ghiyas Setiawan",
                        "nim", "G84180005"
                ));
    }
}
