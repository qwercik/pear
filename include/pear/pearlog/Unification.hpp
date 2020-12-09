#pragma once

#include <list>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/Substitution.hpp>

namespace pear::pearlog {
    class Unification {
    public:
        Unification(const ast::Term *first, const ast::Term *second);
        std::list<Substitution> getSubstitutions() const;

    private:
        const ast::Term *first;
        const ast::Term *second;

        std::list<Substitution> substitutions;
    };
}
