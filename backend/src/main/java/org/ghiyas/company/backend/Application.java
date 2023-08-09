package org.ghiyas.company.backend;

import org.ghiyas.company.backend.entity.AccountEntity;
import org.ghiyas.company.backend.service.AccountService;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class Application {
	public static void main(String[] args) {
		SpringApplication.run(Application.class, args);
	}

	@Bean
	public CommandLineRunner runner(
			AccountService accountService
	) {
		return args -> {
			AccountEntity account1 = new AccountEntity("Aprijal Ghiyas Setiawan", "aprijalghiyas@gmail.com", "subang12345");
			accountService.saveAccount(account1);
		};
	}
}
