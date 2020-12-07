#pragma once

#include <pear/ast/Term.hpp>

namespace pear {
    class Executor {
    public:
        virtual void execute(ast::Term& tree) = 0;
    };
}

