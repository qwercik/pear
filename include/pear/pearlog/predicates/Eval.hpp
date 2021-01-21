#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class Eval : public BuiltinPredicate {
    public:
        class Instance : public BuiltinPredicate::Instance {
        public:
            Instance(const ast::Term::Pointer& term);
            bool next() override;

        private:
            static bool evaluateTree(const ast::Term::Pointer& term, double& result);

            ast::Term::Pointer expression;
            ast::Term::Pointer result;
            bool alreadyCalled = false;
        };

        explicit Eval(Interpreter& interpreter);
        std::unique_ptr<Predicate::Instance> createInstanceBackend(const ast::Term::Pointer& term) const override;
        bool unify(const ast::Term::Pointer& term) const override;
    };
}