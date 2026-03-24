// node.cpp
#include "node.h"
#include <sstream>

NumberNode::NumberNode(const Token& token) : token(token) {}

std::string NumberNode::to_string() const {
    return "NumberNode(" + token.value + ")";
}

StringNode::StringNode(const Token& token) : token(token) {}

std::string StringNode::to_string() const {
    return "StringNode(\"" + token.value + "\")";
}

VarNode::VarNode(const Token& name_token) : name_token(name_token) {}

std::string VarNode::to_string() const {
    return "VarNode(" + name_token.value + ")";
}

UnaryMinusNode::UnaryMinusNode(std::shared_ptr<Node> expr) : expr(std::move(expr)) {}

std::string UnaryMinusNode::to_string() const {
    return "UnaryMinusNode(" + expr->to_string() + ")";
}

BinOpNode::BinOpNode(std::shared_ptr<Node> left, const Token& op, std::shared_ptr<Node> right)
    : left(std::move(left)), op(op), right(std::move(right)) {}

std::string BinOpNode::to_string() const {
    return "BinOpNode(" + left->to_string() + ", " + op.value + ", " + right->to_string() + ")";
}

PrintNode::PrintNode(std::shared_ptr<Node> value) : value(std::move(value)) {}

std::string PrintNode::to_string() const {
    return "PrintNode(" + value->to_string() + ")";
}

LetNode::LetNode(std::string name, std::shared_ptr<Node> value)
    : name(std::move(name)), value(std::move(value)) {}

std::string LetNode::to_string() const {
    return "LetNode(" + name + ", " + value->to_string() + ")";
}

AssignNode::AssignNode(std::string name, std::shared_ptr<Node> value)
    : name(std::move(name)), value(std::move(value)) {}

std::string AssignNode::to_string() const {
    return "AssignNode(" + name + ", " + value->to_string() + ")";
}

TraceNode::TraceNode(std::shared_ptr<Node> expr) : expr(std::move(expr)) {}

std::string TraceNode::to_string() const {
    return "TraceNode(" + expr->to_string() + ")";
}

TimesNode::TimesNode(std::shared_ptr<Node> count_expr, std::shared_ptr<Node> body)
    : count_expr(std::move(count_expr)), body(std::move(body)) {}

std::string TimesNode::to_string() const {
    return "TimesNode(" + count_expr->to_string() + ", " + body->to_string() + ")";
}

ReadNode::ReadNode(Token at) : at(std::move(at)) {}

std::string ReadNode::to_string() const {
    return "ReadNode()";
}

RandNode::RandNode(Token at, std::shared_ptr<Node> hi_expr) : at(std::move(at)), hi_expr(std::move(hi_expr)) {}

std::string RandNode::to_string() const {
    return "RandNode(" + hi_expr->to_string() + ")";
}

SleepNode::SleepNode(Token at, std::shared_ptr<Node> ms_expr) : at(std::move(at)), ms_expr(std::move(ms_expr)) {}

std::string SleepNode::to_string() const {
    return "SleepNode(" + ms_expr->to_string() + ")";
}

ProgramNode::ProgramNode(std::vector<std::shared_ptr<Node>> statements)
    : statements(std::move(statements)) {}

std::string ProgramNode::to_string() const {
    std::ostringstream oss;
    oss << "ProgramNode(";
    for (size_t i = 0; i < statements.size(); ++i) {
        if (i) oss << ", ";
        oss << statements[i]->to_string();
    }
    oss << ")";
    return oss.str();
}
