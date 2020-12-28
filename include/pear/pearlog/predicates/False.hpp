#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPrediacte.hpp>

namespace pear::pearlog::predicates {
    class False : public BuiltinPredicate {
    public:
        virtual bool unify(const ast::Term::Pointer& term) const override;
        virtual bool execute(const ast::Term::Pointer& term) const override;
    };
}
