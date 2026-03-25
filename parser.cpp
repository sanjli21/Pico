// parser.cpp
#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), pos(0), current_token(Token(TokenType::UNKNOWN, "", 0)) {
    if (!tokens.empty()) {
        current_token = tokens[pos];
    }
}

void Parser::advance() {
    pos++;
    if (pos < tokens.size()) {
        current_token = tokens[pos];
    } else {
        current_token = Token(TokenType::UNKNOWN, "", tokens.empty() ? 0 : tokens.back().position);
    }
}

void Parser::skip_separators() {
    while (pos < tokens.size() &&
           (current_token.type == TokenType::NEWLINE || current_token.type == TokenType::SEMICOLON)) {
        advance();
    }
}

Token Parser::peek(size_t ahead) const {
    size_t i = pos + ahead;
    if (i >= tokens.size()) {
        return Token(TokenType::UNKNOWN, "", tokens.empty() ? 0 : tokens.back().position);
    }
    return tokens[i];
}

std::shared_ptr<Node> Parser::print_statement() {
    if (current_token.type != TokenType::PRINT) {
        return nullptr;
    }
    advance();
    auto expr = expression();
    if (!expr) {
        return nullptr;
    }
    return std::make_shared<PrintNode>(expr);
}

std::shared_ptr<Node> Parser::trace_statement() {
    if (current_token.type != TokenType::TRACE) {
        return nullptr;
    }
    advance();
    auto expr = expression();
    if (!expr) {
        return nullptr;
    }
    return std::make_shared<TraceNode>(expr);
}

std::shared_ptr<Node> Parser::let_statement() {
    if (current_token.type != TokenType::LET) {
        return nullptr;
    }
    advance();
    if (current_token.type != TokenType::IDENTIFIER) {
        return nullptr;
    }
    std::string name = current_token.value;
    if (name == "that") {
        return nullptr;
    }
    advance();
    if (current_token.type != TokenType::EQUALS) {
        return nullptr;
    }
    advance();
    auto expr = expression();
    if (!expr) {
        return nullptr;
    }
    return std::make_shared<LetNode>(name, expr);
}

std::shared_ptr<Node> Parser::assign_statement() {
    if (current_token.type != TokenType::IDENTIFIER) {
        return nullptr;
    }
    if (peek(1).type != TokenType::EQUALS) {
        return nullptr;
    }
    std::string name = current_token.value;
    if (name == "that") {
        return nullptr;
    }
    advance();
    advance();
    auto expr = expression();
    if (!expr) {
        return nullptr;
    }
    return std::make_shared<AssignNode>(name, expr);
}

std::shared_ptr<Node> Parser::factor() {
    Token token = current_token;

    if (token.type == TokenType::MINUS) {
        advance();
        auto inner = factor();
        if (!inner) {
            return nullptr;
        }
        return std::make_shared<UnaryMinusNode>(inner);
    }

    if (token.type == TokenType::READ) {
        Token at = token;
        advance();
        return std::make_shared<ReadNode>(at);
    }

    if (token.type == TokenType::RAND) {
        Token at = token;
        advance();
        auto hi = factor();
        if (!hi) {
            return nullptr;
        }
        return std::make_shared<RandNode>(at, hi);
    }

    if (token.type == TokenType::SLEEP) {
        Token at = token;
        advance();
        auto ms = factor();
        if (!ms) {
            return nullptr;
        }
        return std::make_shared<SleepNode>(at, ms);
    }

    if (token.type == TokenType::NUMBER) {
        advance();
        return std::make_shared<NumberNode>(token);
    }

    if (token.type == TokenType::STRING) {
        advance();
        return std::make_shared<StringNode>(token);
    }

    if (token.type == TokenType::IDENTIFIER) {
        advance();
        return std::make_shared<VarNode>(token);
    }

    if (token.type == TokenType::LPAREN) {
        advance();
        auto expr = expression();
        if (!expr) {
            return nullptr;
        }
        if (current_token.type != TokenType::RPAREN) {
            return nullptr;
        }
        advance();
        return expr;
    }

    return nullptr;
}

std::shared_ptr<Node> Parser::term() {
    auto left = factor();
    if (!left) {
        return nullptr;
    }

    while (current_token.type == TokenType::MULTIPLY || current_token.type == TokenType::DIVIDE ||
           current_token.type == TokenType::MODULO) {
        Token op = current_token;
        advance();
        auto right = factor();
        if (!right) {
            return nullptr;
        }
        left = std::make_shared<BinOpNode>(left, op, right);
    }

    return left;
}

std::shared_ptr<Node> Parser::expression() {
    auto left = term();
    if (!left) {
        return nullptr;
    }

    while (current_token.type == TokenType::PLUS || current_token.type == TokenType::MINUS) {
        Token op = current_token;
        advance();
        auto right = term();
        if (!right) {
            return nullptr;
        }
        left = std::make_shared<BinOpNode>(left, op, right);
    }

    return left;
}

std::shared_ptr<Node> Parser::parse_statement() {
    if (current_token.type == TokenType::PRINT) {
        return print_statement();
    }
    if (current_token.type == TokenType::LET) {
        return let_statement();
    }
    if (current_token.type == TokenType::TRACE) {
        return trace_statement();
    }
    if (current_token.type == TokenType::IDENTIFIER && peek(1).type == TokenType::EQUALS) {
        return assign_statement();
    }

    auto expr = expression();
    if (!expr) {
        return nullptr;
    }
    if (current_token.type == TokenType::TIMES) {
        advance();
        auto body = parse_statement();
        if (!body) {
            return nullptr;
        }
        return std::make_shared<TimesNode>(expr, body);
    }
    return expr;
}

std::pair<std::shared_ptr<Node>, Error> Parser::parse() {
    skip_separators();
    if (pos >= tokens.size()) {
        return { nullptr, Error("Empty program", 0) };
    }

    std::vector<std::shared_ptr<Node>> statements;

    while (pos < tokens.size()) {
        skip_separators();
        if (pos >= tokens.size()) {
            break;
        }

        auto stmt = parse_statement();
        if (!stmt) {
            return { nullptr, Error("Syntax error", current_token.position) };
        }
        statements.push_back(stmt);
        skip_separators();
    }

    if (statements.empty()) {
        return { nullptr, Error("Empty program", 0) };
    }

    return { std::make_shared<ProgramNode>(std::move(statements)), Error() };
}
