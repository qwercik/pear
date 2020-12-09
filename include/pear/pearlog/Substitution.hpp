#pragma once

#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::pearlog {
    class Substitution : public ast::TermVisitor {
    public:
        Substitution(const ast::Variable *destination, const ast::Term *source);
        void apply(ast::Term *term);
 
        virtual void visit(ast::Literal* literal) override;
        virtual void visit(ast::Variable* variable) override;
        virtual void visit(ast::Function* function) override;

        const ast::Variable *getDestination() const;
        const ast::Term *getSource() const;

    private:
        const ast::Variable *destination;
        const ast::Term *source;
    };
}
