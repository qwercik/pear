#pragma once

#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Node {
    public:
        enum class Type {
            VARIABLE,
            FUNCTION,
            LITERAL
        };

        Node(Type type, const lexer::Lexeme& lexeme);
        
        Type getType() const;
        const lexer::Lexeme& getLexeme() const;
        Node *getParent() const;
        bool hasParent() const;
        const std::list<std::shared_ptr<Node>>& getChildren() const;

        Node *addNextChild(Node *child);

    private:
        Type type;
        lexer::Lexeme lexeme;
        Node *parent;
        std::list<std::shared_ptr<Node>> children;
    };
}
