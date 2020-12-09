#pragma once

#include <pear/ast/Term.hpp>

namespace pear {
    class Executor {
    public:
        virtual void execute(ast::Term::Pointer tree) = 0;
    };
}

