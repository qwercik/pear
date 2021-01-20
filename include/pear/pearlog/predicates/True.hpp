#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class True : public BuiltinPredicate {
    public:
        class Instance : public BuiltinPredicate::Instance {
        public:
            bool next() override;

        private:
            bool alreadyCalled = false;
        };

        explicit True(Interpreter& interpreter);
        std::unique_ptr<Predicate::Instance> createInstanceBackend(const ast::Term::Pointer& term) const override;
        bool unify(const ast::Term::Pointer& term) const override;
    };
}
