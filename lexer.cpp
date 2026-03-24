// lexer.cpp
#include "lexer.h"
#include <cctype>
#include <unordered_map>

Lexer::Lexer(const std::string& filename, const std::string& text)
    : filename(filename), text(text), pos(0) {
    current_char = text[pos];
}

void Lexer::advance() {
    pos++;
    current_char = pos < text.size() ? text[pos] : '\0';
}

void Lexer::skip_whitespace() {
    while (current_char == ' ' || current_char == '\t' || current_char == '\r') {
        advance();
    }
}

Token Lexer::make_number() {
    size_t start = pos;
    std::string num_str;
    bool has_dot = false;

    while (isdigit(current_char) || current_char == '.') {
        if (current_char == '.') {
            if (has_dot) break;
            has_dot = true;
        }
        num_str += current_char;
        advance();
    }

    return Token(TokenType::NUMBER, num_str, start);
}

Token Lexer::make_identifier() {
    size_t start = pos;
    std::string id_str;

    while (isalnum(current_char) || current_char == '_') {
        id_str += current_char;
        advance();
    }

    static std::unordered_map<std::string, TokenType> keywords = {
        {"print", TokenType::PRINT},
        {"let", TokenType::LET},
        {"trace", TokenType::TRACE},
        {"times", TokenType::TIMES},
        {"read", TokenType::READ},
        {"rand", TokenType::RAND},
        {"sleep", TokenType::SLEEP}
    };

    TokenType type = keywords.count(id_str) ? keywords[id_str] : TokenType::IDENTIFIER;
    return Token(type, id_str, start);
}

Token Lexer::make_string() {
    size_t start = pos;
    std::string str_val;
    advance();

    while (current_char != '"' && current_char != '\0') {
        str_val += current_char;
        advance();
    }

    if (current_char == '"') advance();
    return Token(TokenType::STRING, str_val, start);
}

Token Lexer::make_operator() {
    char op_char = current_char;
    size_t start = pos;
    advance();

    switch (op_char) {
        case '+': return Token(TokenType::PLUS, "+", start);
        case '-': return Token(TokenType::MINUS, "-", start);
        case '*': return Token(TokenType::MULTIPLY, "*", start);
        case '/': return Token(TokenType::DIVIDE, "/", start);
        case '%': return Token(TokenType::MODULO, "%", start);
        case '(': return Token(TokenType::LPAREN, "(", start);
        case ')': return Token(TokenType::RPAREN, ")", start);
        case '=': return Token(TokenType::EQUALS, "=", start);
        case ';': return Token(TokenType::SEMICOLON, ";", start);
        default:  return Token(TokenType::UNKNOWN, std::string(1, op_char), start);
    }
}

std::pair<std::vector<Token>, Error> Lexer::make_tokens() {
    std::vector<Token> tokens;

    while (current_char != '\0') {
        if (current_char == ' ' || current_char == '\t' || current_char == '\r') {
            skip_whitespace();
        } else if (current_char == '\n') {
            tokens.push_back(Token(TokenType::NEWLINE, "\\n", pos));
            advance();
        } else if (isdigit(current_char)) {
            tokens.push_back(make_number());
        } else if (isalpha(current_char)) {
            tokens.push_back(make_identifier());
        } else if (current_char == '"') {
            tokens.push_back(make_string());
        } else {
            tokens.push_back(make_operator());
        }
    }

    return { tokens, Error() };
}
