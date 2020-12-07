#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    Term::Term(const lexer::Lexeme& lexeme) :
        lexeme(lexeme)
    {
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

    Term *Term::addNextChild(Term *child) {
        child->parent = this;
        this->children.emplace_back(child);
        return child;
    }

    const std::list<Term::Pointer>& Term::getChildren() const {
        return this->children;
    }

    bool Term::isVariable() const {
        return this->lexeme.getToken().isIdentifier() && this->children.empty();
    }

    bool Term::isLiteral() const {
        return this->lexeme.getToken().isLiteral();
    }

    bool Term::isFunction() const {
        return this->lexeme.getToken().isIdentifier() && !this->children.empty();
    }
}

