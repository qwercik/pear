#pragma once

#include <pear/ast/Term.hpp>

namespace pear {
    class Executor {
    public:
        virtual bool execute(const ast::Term::Pointer& term) = 0;
    };
}
