#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>

namespace pear::pearlog::predicates {
    class Eval : public BuiltinPredicate {
    public:
        virtual bool execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const override;
    };
}
