// run.h
#pragma once
#include <string>
#include "value.h"
#include "error.h"

struct RunOptions {
    bool dump_tokens = false;
};

std::pair<Value, Error> run(const std::string& filename, const std::string& code,
                            const RunOptions& options = RunOptions{});
