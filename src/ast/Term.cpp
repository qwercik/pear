#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <iostream>

namespace pear::ast {
    Term::Term(Term::Type type, const lexer::Lexeme& lexeme) :
        type(type),
        lexeme(lexeme)
    {
    }

    Term::Term(const Term& term) {
        this->type = term.type;
        this->lexeme = term.lexeme;
        this->parent = nullptr;

        for (const auto& child : term.children) {
            this->addNextChild(std::make_unique<Term>(*child));
        }
    }


    void Term::addNextChild(Term::Pointer&& term) {
        this->insertChild(this->children.end(), std::move(term));
    }

    void Term::replaceChild(Term::Iterator iterator, Term::Pointer&& term) {
        *iterator = std::move(term);
        (*iterator)->parent = this;
        (*iterator)->parentListIterator = iterator;
    }

    void Term::insertChild(Term::Iterator iterator, Term::Pointer&& term) {
        iterator = this->children.insert(iterator, std::move(term));
        (*iterator)->parent = this;
        (*iterator)->parentListIterator = iterator;
    }

    Term::Pointer Term::dropChild(Term::Iterator iterator) {
        auto pointer = std::move(*iterator);
        this->children.erase(iterator);
        pointer->parent = nullptr;

        return pointer;
    }

    bool Term::hasParent() const {
        return this->parent != nullptr;
    }
    
    Term *Term::getParent() {
        return this->parent;
    }

    Term::Type Term::getType() const {
        return this->type;
    }

    const lexer::Lexeme& Term::getLexeme() const {
        return this->lexeme;
    }
    
    const Term::List& Term::getChildren() const {
        return this->children;
    }

    Term::List& Term::getChildren() {
        return this->children;
    }

    Term::Iterator Term::getParentListIterator() const {
        return this->parentListIterator;
    }

    bool Term::operator==(const Term& term) const {
        if (this->type != term.type) {
            return false;
        }

        auto firstIt = this->children.begin();
        auto firstEnd = this->children.end();
        auto secondIt = term.children.begin();
        auto secondEnd = term.children.end();

        while (firstIt != firstEnd && secondIt != secondEnd) {
            if (**firstIt != **secondIt) {
                return false;
            }

            firstIt++;
            secondIt++;
        }

        // Test whether both containers have the same size
        return firstIt == firstEnd && secondIt == secondEnd;
    }

    bool Term::operator!=(const Term& term) const {
        return !(*this == term);
    }

    Term::Pointer Term::clone() const {
        return std::make_unique<Term>(*this);
    }
}
