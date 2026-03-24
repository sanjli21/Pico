// node.h
#pragma once
#include <memory>
#include <string>
#include <vector>
#include "token.h"

class Node {
public:
    virtual ~Node() = default;
    virtual std::string to_string() const = 0;
};

class NumberNode : public Node {
public:
    Token token;
    explicit NumberNode(const Token& token);
    std::string to_string() const override;
};

class StringNode : public Node {
public:
    Token token;
    explicit StringNode(const Token& token);
    std::string to_string() const override;
};

class VarNode : public Node {
public:
    Token name_token;
    explicit VarNode(const Token& name_token);
    std::string to_string() const override;
};

class UnaryMinusNode : public Node {
public:
    std::shared_ptr<Node> expr;
    explicit UnaryMinusNode(std::shared_ptr<Node> expr);
    std::string to_string() const override;
};

class BinOpNode : public Node {
public:
    std::shared_ptr<Node> left;
    Token op;
    std::shared_ptr<Node> right;

    BinOpNode(std::shared_ptr<Node> left, const Token& op, std::shared_ptr<Node> right);
    std::string to_string() const override;
};

class PrintNode : public Node {
public:
    std::shared_ptr<Node> value;

    explicit PrintNode(std::shared_ptr<Node> value);
    std::string to_string() const override;
};

class LetNode : public Node {
public:
    std::string name;
    std::shared_ptr<Node> value;

    LetNode(std::string name, std::shared_ptr<Node> value);
    std::string to_string() const override;
};

class AssignNode : public Node {
public:
    std::string name;
    std::shared_ptr<Node> value;

    AssignNode(std::string name, std::shared_ptr<Node> value);
    std::string to_string() const override;
};

class TraceNode : public Node {
public:
    std::shared_ptr<Node> expr;

    explicit TraceNode(std::shared_ptr<Node> expr);
    std::string to_string() const override;
};

class TimesNode : public Node {
public:
    std::shared_ptr<Node> count_expr;
    std::shared_ptr<Node> body;

    TimesNode(std::shared_ptr<Node> count_expr, std::shared_ptr<Node> body);
    std::string to_string() const override;
};

/// Reads one line from stdin; value is a number if the whole line parses as numeric, else a string.
class ReadNode : public Node {
public:
    Token at;

    explicit ReadNode(Token at);
    std::string to_string() const override;
};

class RandNode : public Node {
public:
    Token at;
    std::shared_ptr<Node> hi_expr;

    RandNode(Token at, std::shared_ptr<Node> hi_expr);
    std::string to_string() const override;
};

class SleepNode : public Node {
public:
    Token at;
    std::shared_ptr<Node> ms_expr;

    SleepNode(Token at, std::shared_ptr<Node> ms_expr);
    std::string to_string() const override;
};

class ProgramNode : public Node {
public:
    std::vector<std::shared_ptr<Node>> statements;

    explicit ProgramNode(std::vector<std::shared_ptr<Node>> statements);
    std::string to_string() const override;
};
