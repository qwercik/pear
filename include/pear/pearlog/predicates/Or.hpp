#pragma once

#include <pear/ast/Term.hpp>
#include <pear/pearlog/BuiltinPredicate.hpp>
#include <pear/pearlog/Interpreter.hpp>

namespace pear::pearlog::predicates {
    class Or : public RuntimeDefinedPredicate {
    public:
        bool unify(const ast::Term::Pointer& term) const override;

        void in(Interpreter& interpreter, const ast::Term::Pointer& term) override;
        bool next() override;
        void out() override;

    private:
        Interpreter *interpreter = nullptr;

        ast::Term::Pointer term;
        PredicatesManager::ConstIterator iterator;
        bool predicateInitialized = false;

        std::size_t childrenNumber = 0;
        std::size_t currentChild = 0;
    };
}
