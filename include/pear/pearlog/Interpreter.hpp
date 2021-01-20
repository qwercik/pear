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

        void call(const ast::Term::Pointer& term);
        bool next();
        void back();

        void updateScopeId(int diff);

        PredicatesManager& getPredicatesManager();
        std::stack<std::list<Substitution>>& getSubstitutions();
        std::stack<PredicatesManager::ConstIterator>& getIterators();
        int getScopeId() const;

    private:
        PredicatesManager predicatesManager;
        std::stack<std::list<Substitution>> substitutions;
        std::stack<PredicatesManager::ConstIterator> iterators;
        std::stack<ast::Term::Pointer> terms;
        int currentScopeId = 0;
    };
};
