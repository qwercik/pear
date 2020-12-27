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
            auto childCopy = std::make_unique<Term>(*child);
            childCopy->parent = this;
            auto iterator = this->children.insert(this->children.end(), std::move(childCopy));
            (*iterator)->parentListIterator = iterator;
        }

        std::cout << "po skopiowaniu " << TermPrinter(this) << '\n';
    }

    bool Term::hasParent() const {
        return this->parent != nullptr;
    }
    
    Term *Term::getParent() const {
        return this->parent;
    }

    Term *Term::addNextChild(Term::Pointer&& child) {
        auto pointer = child.get();
        this->insertChild(this->children.end(), std::move(child));
        return pointer;
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

    Term::Pointer Term::move() {
        if (this->parent == nullptr) {
            // to nie powinno mieć miejsca
        }

        auto pointer = std::move(*this->parentListIterator);
        this->parent->children.erase(this->parentListIterator);
        this->parent = nullptr;
        return pointer;
    }

    const lexer::Lexeme& Term::getLexeme() const {
        return this->lexeme;
    }

    Term::Type Term::getType() const {
        return this->type;
    }

    Term *Term::replace(Term::Pointer&& term) {
        std::cout << "Jestem w termie 1 " << this->getLexeme().getContent() << " " << this->hasParent() << '\n';
        std::cout << "Jestem w termie 2 " << term->getLexeme().getContent() << " " << term->hasParent() << '\n';

        std::cout << "begin\n";
        std::cout << (*this->parentListIterator)->getLexeme().getContent() << '\n';
        std::cout << "end\n";

        auto pointer = term.get();
        term->parent = this->parent;
        term->parentListIterator = this->parentListIterator;
        *this->parentListIterator = std::move(term);
        return pointer;
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
        auto newIterator = this->children.insert(iterator, std::move(child));
        (*newIterator)->parentListIterator = newIterator;
    }
}

