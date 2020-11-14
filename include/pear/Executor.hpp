#pragma once

#include <pear/ast/AbstractSyntaxTree.hpp>

namespace pear {
    class Executor {
    public:
        virtual void execute(ast::AbstractSyntaxTree& tree) = 0;
    };
}

