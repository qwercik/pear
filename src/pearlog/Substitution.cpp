#include <pear/pearlog/Substitution.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Literal.hpp>
#include <iostream>

namespace pear::pearlog {
    Substitution::Visitor::Visitor(const ast::Variable *destination, ast::Term *source) :
        destination(destination),
        source(source)
    {
    }

    void Substitution::Visitor::visit(ast::Variable* variable) {
        if (*this->destination == *variable) {
            auto cloned = this->source->clone();
            variable->replace(cloned);
        }
    }
    
    void Substitution::Visitor::visit(ast::Literal* literal) {

    }

    void Substitution::Visitor::visit(ast::Function* function) {
        for (auto& child : function->getArguments()) {
            child->accept(this); // ?!?
        }
    }


    Substitution::Substitution(const ast::Variable *destination, ast::Term *source) :
        destination(destination),
        source(source)
    {
    }

    void Substitution::apply(ast::Term* term) const {
        Visitor visitor(this->destination, this->source);
        term->accept(&visitor);
    }

    void Substitution::apply(Substitution& substitution) const {
        this->apply(substitution.source);
    }

    void Substitution::apply(std::list<Substitution>& substitutions) const {
        for (auto& substitution : substitutions) {
            this->apply(substitution);
        }

        substitutions.push_back(*this);
    }


    const ast::Variable *Substitution::getDestination() const {
        return this->destination;
    }

    const ast::Term *Substitution::getSource() const {
        return this->source;
    }
}

