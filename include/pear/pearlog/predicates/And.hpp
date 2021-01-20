#pragma once

#include <stack>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class And : public RuntimeDefinedPredicate {
    public:
        bool unify(const ast::Term::Pointer& term) const override;

        void in(Interpreter& interpreter, const ast::Term::Pointer& term) override;
        bool next() override;
        void out() override;

    private:
        Interpreter *interpreter = nullptr;

        std::stack<PredicatesManager::ConstIterator> iterators;
        std::stack<std::list<Substitution>> substitutions;
        std::stack<ast::Term::Pointer> terms;
        std::stack<bool> predicateInitialized;

        std::size_t childrenNumber = 0;
    };
}
