#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog {
    class RuntimeDefinedPredicate : public Predicate {
    public:
        explicit RuntimeDefinedPredicate(const ast::Term& definition);

        bool unify(const ast::Term::Pointer& pointer) const override;
        bool in(Interpreter& context, const ast::Term::Pointer& term) const override;
        bool next(Interpreter& context, const ast::Term::Pointer& term) const override;
        bool out(Interpreter& context, const ast::Term::Pointer& term) const override;

    private:
        void toggleVariablesScopeId(ast::Term::Pointer& pointer, int currentScopeId) const;

        ast::Term::Pointer header;
        ast::Term::Pointer body;
    };
}
