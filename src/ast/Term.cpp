#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    Term::Term(const lexer::Lexeme& lexeme) :
        lexeme(lexeme)
    {
    }

    Term::Term(const Term& term) {
        this->lexeme = term.lexeme;
        this->children = term.children;
    }

    const lexer::Lexeme& Term::getLexeme() const {
        return this->lexeme;
    }

    bool Term::hasParent() const {
        return this->parent;
    }
    
    Term *Term::getParent() const {
        return this->parent;
    }

    Term *Term::addNextChild(std::shared_ptr<Term> child) {
        this->insertChild(this->children.end(), child);
        return child.get();
    }

    const Term::List& Term::getChildren() const {
        return this->children;
    }

    bool Term::isVariable() const {
        return this->lexeme.getToken()->isIdentifier() && this->children.empty();
    }

    bool Term::isLiteral() const {
        return this->lexeme.getToken()->isLiteral();
    }

    bool Term::isFunction() const {
        return this->lexeme.getToken()->isIdentifier() && !this->children.empty();
    }

    void Term::replace(std::shared_ptr<Term> term) {
        auto iterator = this->parentListIterator;

        this->parent->insertChild(iterator, term);
        this->parent->children.erase(iterator);
    }

    void Term::insertChild(const Term::Iterator& iterator, std::shared_ptr<Term> child) {
        child->parent = this;
        this->children.insert(iterator, child);
        child->parentListIterator = iterator;
    }

    void Term::dropChild(const Term::Iterator& iterator) {
        this->children.erase(iterator);
    }
}

