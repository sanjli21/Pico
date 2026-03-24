// token.h
#pragma once
#include <string>

enum class TokenType {
    NUMBER,
    IDENTIFIER,
    KEYWORD,
    STRING,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    LPAREN,
    RPAREN,
    PRINT,
    LET,
    TRACE,
    TIMES,
    READ,
    RAND,
    SLEEP,
    EQUALS,
    SEMICOLON,
    NEWLINE,
    UNKNOWN
};

class Token {
public:
    TokenType type;
    std::string value;
    size_t position;

    Token(TokenType type, const std::string& value, size_t position);

    std::string to_string() const;
};
