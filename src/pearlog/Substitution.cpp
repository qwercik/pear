#include <pear/pearlog/Substitution.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Literal.hpp>

namespace pear::pearlog {
    Substitution::Substitution(const ast::Variable *destination, const ast::Term *source) :
        destination(destination),
        source(source)
    {
    }

    void Substitution::apply(ast::Term* term) {
        term->accept(this);
    }

    void Substitution::visit(ast::Variable* variable) {
        if (*this->destination != *variable) {
            variable->replace(new ast::Variable(*this->destination));
        }
    }
    
    void Substitution::visit(ast::Literal* literal) {
    }

    void Substitution::visit(ast::Function* function) {
        for (auto& child : function->getArguments()) {
            this->apply(child.get());
        }
    }

    const ast::Variable *Substitution::getDestination() const {
        return this->destination;
    }

    const ast::Term *Substitution::getSource() const {
        return this->source;
    }
}

