#pragma once

#include <list>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::pearlog {
    class Substitution {
    public:
        Substitution(const ast::Variable *destination, ast::Term *source);
        void apply(ast::Term *term) const;
        void apply(Substitution &substitution) const;
        void apply(std::list<Substitution>& substitutions) const;
 
        const ast::Variable *getDestination() const;
        const ast::Term *getSource() const;

    private:
        class Visitor : public ast::TermVisitor {
        public:
            Visitor(const ast::Variable *destination, ast::Term *source);

            virtual void visit(ast::Literal* literal) override;
            virtual void visit(ast::Variable* variable) override;
            virtual void visit(ast::Function* function) override;

        private:
            const ast::Variable *const destination;
            ast::Term *source;
        };

        std::shared_ptr<ast::Variable> destination;
        std::shared_ptr<ast::Term> source;
    };
}
