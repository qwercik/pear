#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class Call : public RuntimeDefinedPredicate {
    public:
        bool unify(const ast::Term::Pointer& term) const override;

        void in(Interpreter& interpreter, const ast::Term::Pointer& term) override;
        bool next() override;
        void out() override;
    };
}
