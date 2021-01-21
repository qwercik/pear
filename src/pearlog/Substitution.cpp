#include <pear/pearlog/Substitution.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Literal.hpp>
#include <iostream>

namespace pear::pearlog {
    Substitution::Substitution(const ast::Term::Pointer& destination, const ast::Term::Pointer& source) :
        destination(destination->clone()),
        source(source->clone())
    {
    }

    Substitution::Substitution(const Substitution& substitution) :
        Substitution::Substitution(substitution.destination, substitution.source)
    {
    }

    void Substitution::apply(ast::Term::Pointer& term) const {
        if (term->getType() == ast::Term::Type::VARIABLE) {
            if (*this->destination == *term) {
                term = this->source->clone();
            }
        } else if (term->getType() == ast::Term::Type::FUNCTION) {
            for (auto& child : term->getChildren()) {
                this->apply(child);
            }
        }
    }

    void Substitution::apply(Substitution& substitution) const {
        this->apply(substitution.source);
    }

    ast::Term::Pointer& Substitution::getDestination() {
        return this->destination;
    }

    const ast::Term::Pointer& Substitution::getDestination() const {
        return this->destination;
    }

    ast::Term::Pointer& Substitution::getSource() {
        return this->source;
    }

    const ast::Term::Pointer& Substitution::getSource() const {
        return this->source;
    }
}
