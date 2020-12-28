#pragma once

#include <memory>
#include <pear/ast/Term.hpp>

namespace pear::pearlog {
    class Predicate {
    public:
        using Pointer = std::unique_ptr<Predicate>;
    
        virtual bool unify(const ast::Term::Pointer& term) const = 0;
        virtual bool execute(const ast::Term::Pointer& term) const = 0;
    };
}
