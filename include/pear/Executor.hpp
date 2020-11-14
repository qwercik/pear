#pragma once

#include <pear/ast/Tree.hpp>

namespace pear {
    class Executor {
    public:
        virtual void execute(ast::Tree& tree) = 0;
    };
}

