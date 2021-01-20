#pragma once

#include <list>
#include <stack>
#include <pear/Executor.hpp>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/PredicatesManager.hpp>
#include <pear/pearlog/Substitution.hpp>

namespace pear::pearlog {
    class Interpreter {
    public:
        Interpreter();
        void execute(const ast::Term::Pointer& term);

        PredicatesManager& getPredicatesManager();
        std::stack<Predicate::Instance>& getInstances();

    private:
        PredicatesManager predicatesManager;
        std::stack<Predicate::Instance> instances;
    };
};
