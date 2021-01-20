#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class Print : public BuiltinPredicate {
    public:
        class Instance : public BuiltinPredicate::Instance {
        public:
            Instance(const ast::Term::Pointer& term);
            bool next() override;

        private:
            const ast::Term::Pointer& term;
            bool alreadyCalled = false;
        };

        explicit Print(Interpreter& interpreter);
        std::unique_ptr<Predicate::Instance> createInstanceBackend(const ast::Term::Pointer& term) const override;
        bool unify(const ast::Term::Pointer& term) const override;
    };
}