#pragma once

#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::pearlog {
    class Substitution : public ast::TermVisitor {
    public:
        Substitution(const ast::Variable *variable, const ast::Term *other);
        void apply(ast::Term *term);
 
        virtual void visitLiteral(ast::Literal* literal) override;
        virtual void visitVariable(ast::Variable* variable) override;
        virtual void visitFunction(ast::Function* function) override;

    private:
        const ast::Variable *variable;
        const ast::Term *other;
    };
}
