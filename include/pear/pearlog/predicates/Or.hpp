#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class Or : public BuiltinPredicate {
    public:
        class Instance : public BuiltinPredicate::Instance {
        public:
            Instance(Interpreter& interpreter, const ast::Term::Pointer& term);
            bool next() override;

        private:
            Interpreter& interpreter;
            const ast::Term::Pointer term;
            std::list<ast::Term::Pointer>::const_iterator childIterator;
            std::list<ast::Term::Pointer>::const_iterator endIterator;
            std::unique_ptr<Predicate::Instance> childInstance;
        };

        explicit Or(Interpreter& interpreter);
        std::unique_ptr<Predicate::Instance> createInstanceBackend(const ast::Term::Pointer& term) const override;
        bool unify(const ast::Term::Pointer& term) const override;
    };
}
