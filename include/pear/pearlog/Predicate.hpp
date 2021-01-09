#pragma once

#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/Substitution.hpp>

namespace pear::pearlog {
    class Predicate {
    public:
        using Pointer = std::unique_ptr<Predicate>;

        virtual bool execute(const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const = 0;
    };
}
