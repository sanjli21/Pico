// context.h
#pragma once
#include <ostream>
#include <string>
#include <memory>
#include "symbol_table.h"
#include "value.h"

class Context {
public:
    std::string display_name;
    std::shared_ptr<SymbolTable> symbol_table;
    std::shared_ptr<Context> parent;
    size_t parent_entry_pos;

    /// Last value produced by print, let, assign, trace, times, or a bare expression ("pronoun" `that`).
    Value that_value;
    bool has_that = false;

    /// When non-null, the interpreter prints a step-by-step evaluation log for nested visits.
    std::ostream* trace_stream = nullptr;
    int trace_depth = 0;

    Context(const std::string& display_name, std::shared_ptr<Context> parent = nullptr, size_t parent_entry_pos = 0);

    void set_symbol_table(std::shared_ptr<SymbolTable> new_symbol_table);

    void set_that(const Value& v);
};
