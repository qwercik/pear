#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog {
    class RuntimeDefinedPredicate : public Predicate {
    public:
        class Instance : public Predicate::Instance {
        public:
            Instance(Interpreter& interpreter, const ast::Term::Pointer& header, const ast::Term::Pointer& body, const ast::Term::Pointer& term);
            bool next() override;

        private:
            void toggleVariablesScopeId(ast::Term::Pointer& pointer, int currentScopeId) const;

            Interpreter& interpreter;
            const ast::Term::Pointer& header;
            const ast::Term::Pointer& body;
            ast::Term::Pointer term;
            int scopeId;

            std::unique_ptr<Predicate::Instance> caller;
        };

        explicit RuntimeDefinedPredicate(Interpreter& interpreter, const ast::Term::Pointer & definition);

        std::unique_ptr<Predicate::Instance> createInstanceBackend(const ast::Term::Pointer& term) const override;
        bool unify(const ast::Term::Pointer& term) const override;

    private:
        const ast::Term::Pointer& header;
        const ast::Term::Pointer& body;
    };
}
