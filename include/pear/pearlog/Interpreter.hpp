#pragma once

#include <pear/Executor.hpp>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/PredicatesManager.hpp>

namespace pear::pearlog {
    class Interpreter : public Executor {
    public:
        Interpreter();

        virtual bool execute(const ast::Term::Pointer& term) override;
        bool execute(const ast::Term::Pointer& term, std::list<Substitution>& substitutions);

    private:
        PredicatesManager predicatesManager;
    };
};
