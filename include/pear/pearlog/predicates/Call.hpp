#pragma once

#include <stack>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class Call : public BuiltinPredicate {
    public:
        class Instance : public BuiltinPredicate::Instance {
        public:
            Instance(Interpreter& interpreter, const ast::Term::Pointer& term);
            bool next() override;

        private:
            Interpreter& interpreter;
            const ast::Term::Pointer& child;
            std::unique_ptr<Predicate::Instance> childInstance;
            PredicatesManager::ConstIterator iterator;
        };

        explicit Call(Interpreter& interpreter);

        std::unique_ptr<Predicate::Instance> createCaller(const ast::Term::Pointer& term) const;
        std::unique_ptr<Predicate::Instance> createInstanceBackend(const ast::Term::Pointer& term) const override;
        bool unify(const ast::Term::Pointer& term) const override;
    };
}
