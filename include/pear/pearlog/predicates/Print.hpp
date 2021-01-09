#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class Print : public BuiltinPredicate {
    public:
        virtual bool execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const override;
    };
}
