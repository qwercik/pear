#pragma once

#include <stack>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class And : public BuiltinPredicate {
    public:
        class Instance : public BuiltinPredicate::Instance {
        public:
            Instance(Interpreter& interpreter, const ast::Term::Pointer& term);
            bool next() override;

        private:
            Interpreter& interpreter;
            ast::Term::Pointer term;
            ast::Term::List::const_iterator currentChild;
            ast::Term::List::const_iterator lastChild;
            std::stack<std::unique_ptr<Predicate::Instance>> childInstances;
        };

        explicit And(Interpreter& interpreter);

        std::unique_ptr<Predicate::Instance> createInstanceBackend(const ast::Term::Pointer& term) const override;
        bool unify(const ast::Term::Pointer& term) const override;
    };
}
