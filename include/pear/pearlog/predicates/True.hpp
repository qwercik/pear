#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPrediacte.hpp>

namespace pear::pearlog::predicates {
    class True : public BuiltinPredicate {
    public:
        virtual bool execute(const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const override;
    };
}
