package org.ghiyas.company.backend.config;

import com.auth0.jwt.JWT;
import com.auth0.jwt.algorithms.Algorithm;
import com.fasterxml.jackson.databind.ObjectMapper;
import jakarta.servlet.FilterChain;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;
import org.springframework.stereotype.Component;

import java.io.IOException;
import java.util.Date;
import java.util.Map;
import java.util.stream.Collectors;

@Component
public class JwtAuthenticationFilter extends UsernamePasswordAuthenticationFilter {
    @Value("${jwt.secret}")
    private String jwtSecret;

    public JwtAuthenticationFilter(AuthenticationManager authenticationManager) {
        super.setAuthenticationManager(authenticationManager);
    }

    @Override
    public Authentication attemptAuthentication(HttpServletRequest request, HttpServletResponse response) throws AuthenticationException {
        String email = request.getParameter("email");
        String password = request.getParameter("password");

        return this.getAuthenticationManager().authenticate(
                new UsernamePasswordAuthenticationToken(email, password)
        );
    }

    @Override
    protected void successfulAuthentication(HttpServletRequest request, HttpServletResponse response, FilterChain chain, Authentication authResult) throws IOException {
        User principal = (User) authResult.getPrincipal();
        Algorithm algorithm = Algorithm.HMAC256(this.jwtSecret.getBytes());

        String accessToken = JWT.create()
                .withSubject(principal.getUsername())
                .withExpiresAt(new Date(System.currentTimeMillis() + 60 * 120 * 1000))
                .withIssuer(request.getRequestURI())
                .withClaim("roles", principal.getAuthorities().stream()
                        .map(GrantedAuthority::getAuthority)
                        .collect(Collectors.toList()))
                .sign(algorithm);

        response.setContentType(MediaType.APPLICATION_JSON_VALUE);
        response.setStatus(HttpStatus.OK.value());

        new ObjectMapper().writeValue(
                response.getOutputStream(),
                Map.of(
                        "code", HttpStatus.OK.value(),
                        "status", HttpStatus.OK.getReasonPhrase(),
                        "data", Map.of(
                                "access_token", accessToken
                        )
                )
        );
    }

    @Override
    protected void unsuccessfulAuthentication(HttpServletRequest request, HttpServletResponse response, AuthenticationException failed) throws IOException {
        response.setContentType(MediaType.APPLICATION_JSON_VALUE);
        response.setStatus(HttpStatus.UNAUTHORIZED.value());

        new ObjectMapper().writeValue(
                response.getOutputStream(),
                Map.of(
                        "code", HttpStatus.UNAUTHORIZED.value(),
                        "status", HttpStatus.UNAUTHORIZED.getReasonPhrase()
                )
        );
    }
}
