#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>

namespace pear::pearlog::predicates {
    class Eval : public RuntimeDefinedPredicate {
    public:
        bool unify(const ast::Term::Pointer& term) const override;

        void in(Interpreter& interpreter, const ast::Term::Pointer& term) override;
        bool next() override;
        void out() override;
    };
}
