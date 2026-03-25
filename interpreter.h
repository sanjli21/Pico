// interpreter.h
#pragma once
#include <memory>
#include "node.h"
#include "context.h"
#include "symbol_table.h"
#include "value.h"
#include "error.h"

class Interpreter {
public:
    std::pair<Value, Error> visit(std::shared_ptr<Node> node, Context& context);

private:
    std::pair<Value, Error> visit_NumberNode(std::shared_ptr<NumberNode> node, Context& context);
    std::pair<Value, Error> visit_StringNode(std::shared_ptr<StringNode> node, Context& context);
    std::pair<Value, Error> visit_VarNode(std::shared_ptr<VarNode> node, Context& context);
    std::pair<Value, Error> visit_UnaryMinusNode(std::shared_ptr<UnaryMinusNode> node, Context& context);
    std::pair<Value, Error> visit_BinOpNode(std::shared_ptr<BinOpNode> node, Context& context);
    std::pair<Value, Error> visit_PrintNode(std::shared_ptr<PrintNode> node, Context& context);
    std::pair<Value, Error> visit_LetNode(std::shared_ptr<LetNode> node, Context& context);
    std::pair<Value, Error> visit_AssignNode(std::shared_ptr<AssignNode> node, Context& context);
    std::pair<Value, Error> visit_TraceNode(std::shared_ptr<TraceNode> node, Context& context);
    std::pair<Value, Error> visit_TimesNode(std::shared_ptr<TimesNode> node, Context& context);
    std::pair<Value, Error> visit_ReadNode(std::shared_ptr<ReadNode> node, Context& context);
    std::pair<Value, Error> visit_RandNode(std::shared_ptr<RandNode> node, Context& context);
    std::pair<Value, Error> visit_SleepNode(std::shared_ptr<SleepNode> node, Context& context);
    std::pair<Value, Error> visit_ProgramNode(std::shared_ptr<ProgramNode> node, Context& context);
};
