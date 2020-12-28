#include <pear/pearlog/Substitution.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Literal.hpp>
#include <iostream>

namespace pear::pearlog {
    Substitution::Substitution(const ast::Term *destination, const ast::Term *source) :
        destination(std::make_unique<ast::Term>(*destination)),
        source(std::make_unique<ast::Term>(*source))
    {
    }

    Substitution::Substitution(const Substitution& substitution) :
        Substitution::Substitution(substitution.destination.get(), substitution.source.get())
    {
    }

    void Substitution::apply(ast::Term* term) const {
        if (term->getType() == ast::Term::Type::VARIABLE) {
            if (*this->destination == *term) {
                if (term->hasParent()) {
                    throw new int(997);
                }

                auto iterator = term->getParentListIterator();
                term->getParent()->replaceChild(iterator, std::make_unique<ast::Term>(*this->source));
            }
        } else if (term->getType() == ast::Term::Type::FUNCTION) {
            for (const auto child : term->getChildren()) {
                this->apply(child);
            }
        }
    }

    void Substitution::apply(Substitution& substitution) const {
        this->apply(substitution.source.get());
    }

    const ast::Term *Substitution::getDestination() const {
        return this->destination.get();
    }

    const ast::Term *Substitution::getSource() const {
        return this->source.get();
    }
}
