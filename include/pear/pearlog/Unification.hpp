#pragma once

#include <list>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Literal.hpp>
#include <pear/ast/Function.hpp>
#include <pear/pearlog/Substitution.hpp>

namespace pear::pearlog {
    class Unification {
    public:
        class Result {
        public:
            Result() = default;
            Result(const Result& result);

            const std::list<Substitution>& getSubstitutions() const;
            ast::Term *getTerm() const;
            bool isOk() const;

            friend class Unification;

        private:
            std::list<Substitution> substitutions;
            std::unique_ptr<ast::Term> term;
            bool error = false;
        };

        Unification(const ast::Term::Pointer& first, const ast::Term::Pointer& second);
        const Result& getResult() const;

    private:
        void unifyBackend(const ast::Term::Pointer& first, const ast::Term::Pointer& second);

        std::unique_ptr<ast::Term> first;
        std::unique_ptr<ast::Term> second;
        Result result;
    };
}

