#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
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

        for (const auto& child : term.children) {
            this->children.push_back(std::make_unique<Term>(*child));
        }
    }

    bool Term::hasParent() const {
        return this->parent != nullptr;
    }
    
    Term *Term::getParent() const {
        return this->parent;
    }

    Term *Term::addNextChild(Term::Pointer&& child) {
        auto rawPointer = child.get();
        this->insertChild(this->children.end(), std::move(child));
        return rawPointer;
    }

    std::list<Term*> Term::getChildren() const {
        std::list<Term*> children;
        for (const auto& child : this->children) {
            children.push_back(child.get());
        }
        
        return children;
    }

    std::list<Term::Pointer>&& Term::moveChildren() {
        return std::move(this->children);
    }

    const lexer::Lexeme& Term::getLexeme() const {
        return this->lexeme;
    }

    Term::Type Term::getType() const {
        return this->type;
    }

    Term *Term::replace(Term::Pointer&& term) {
        auto iterator = this->parentListIterator;

        this->parent->insertChild(iterator, std::move(term));
        this->parent->children.erase(iterator);

        return term.get();
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


    void Term::insertChild(const std::list<Term::Pointer>::iterator& iterator, Term::Pointer&& child) {
        child->parent = this;
        child->parentListIterator = iterator;
        this->children.insert(iterator, std::move(child));
    }

    void Term::dropChild(const std::list<Term::Pointer>::iterator& iterator) {
        this->children.erase(iterator);
    }
}

