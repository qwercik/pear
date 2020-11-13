#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Node.hpp>

namespace pear::ast {
    Node::Node(Node::Type type, const lexer::Lexeme& lexeme) :
        type(type),
        lexeme(lexeme),
        parent(nullptr)
    {
    }
    
    Node::Type Node::getType() const {
        return this->type;
    }

    const lexer::Lexeme& Node::getLexeme() const {
        return this->lexeme;
    }
    
    Node *Node::getParent() const {
        return this->parent;
    }

    bool Node::hasParent() const {
        return this->parent;
    }

    const std::list<std::shared_ptr<Node>>& Node::getChildren() const {
        return this->children;
    }

    Node *Node::addNextChild(Node *child) {
        this->children.emplace_back(child);
        return child;
    }
}

