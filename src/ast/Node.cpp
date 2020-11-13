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
    
    Node::NodePointer Node::getParent() const {
        return this->parent;
    }

    bool Node::hasParent() const {
        return this->parent;
    }

    const Node::ChildrenList& Node::getChildren() const {
        return this->children;
    }

    Node::NodePointer Node::addNextChild(Node::ChildNodePointer child) {
        this->children.push_back(std::move(child));
        child->parent = this;
        return this;
    }
}

