#pragma once

#include <list>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Literal.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/TermVisitor.hpp>
#include <pear/pearlog/Substitution.hpp>

namespace pear::pearlog {
    class Unification {
    public:
        struct Result {
            Result(ast::Term *term) :
                term(term)
            {
            }

            std::list<Substitution> substitutions;
            ast::Term *term;
            bool error = false;
        };

        Unification(ast::Term *first, ast::Term *second);
        Result getResult() const;

    private:
        class UnificationVisitor : public ast::TermVisitor {
        public:
            UnificationVisitor(ast::Term *term, Result *result);

            virtual void visit(ast::Variable *variable) override;
            virtual void visit(ast::Literal *literal) override;
            virtual void visit(ast::Function *function) override;

        private:
            ast::Term *term;
            Result *result;
        };

        class VariableVisitor : public ast::TermVisitor {
        public:
            VariableVisitor(ast::Variable *variable, Result *result);

            virtual void visit(ast::Variable *variable) override;
            virtual void visit(ast::Literal *literal) override;
            virtual void visit(ast::Function *function) override;

        private:
            ast::Variable *variable;
            Result *result;
        };

        class LiteralVisitor : public ast::TermVisitor {
        public:
            LiteralVisitor(ast::Literal *literal, Result *result);

            virtual void visit(ast::Variable *variable) override;
            virtual void visit(ast::Literal *literal) override;
            virtual void visit(ast::Function *function) override;

        private:
            ast::Literal *literal;
            Result *result;
        };

        class FunctionVisitor : public ast::TermVisitor {
        public:
            FunctionVisitor(ast::Function *function, Result *result);

            virtual void visit(ast::Variable *variable) override;
            virtual void visit(ast::Literal *literal) override;
            virtual void visit(ast::Function *function) override;

        private:
            ast::Function *function;
            Result *result;
        };


        ast::Term *first;
        ast::Term *second;

        Result result;
    };
}

