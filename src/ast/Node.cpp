#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Node.hpp>

namespace pear::ast {
    Node::Node(const lexer::Lexeme& lexeme) :
        lexeme(lexeme)
    {
    }

    const lexer::Lexeme& Node::getLexeme() const {
        return this->lexeme;
    }

    bool Node::hasParent() const {
        return this->parent;
    }
    
    Node *Node::getParent() const {
        return this->parent;
    }

    Node *Node::addNextChild(Node *child) {
        child->parent = this;
        this->children.emplace_back(child);
        return child;
    }

    const std::list<std::shared_ptr<Node>>& Node::getChildren() const {
        return this->children;
    }

    bool Node::isVariable() const {
        return this->lexeme.getToken().isIdentifier() && this->children.empty();
    }

    bool Node::isLiteral() const {
        return this->lexeme.getToken().isLiteral();
    }

    bool Node::isFunction() const {
        return this->lexeme.getToken().isIdentifier() && !this->children.empty();
    }
}

