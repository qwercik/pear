#pragma once

#include <pear/ast/Term.hpp>

namespace pear {
    class Executor {
    public:
        virtual void execute(const ast::Term::Pointer& term) = 0;
    };
}
