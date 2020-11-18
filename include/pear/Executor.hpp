#pragma once

#include <pear/ast/Node.hpp>

namespace pear {
    class Executor {
    public:
        virtual void execute(ast::Node& tree) = 0;
    };
}

