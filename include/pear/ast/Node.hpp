#pragma once

#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Node {
    public:
        using Pointer = std::shared_ptr<Node>;

        Node() = default;
        Node(const lexer::Lexeme& lexeme);

        const lexer::Lexeme& getLexeme() const;

        bool hasParent() const;
        Node *getParent() const;

        Node *addNextChild(Node *child);
        const std::list<Pointer>& getChildren() const;

        bool isVariable() const;
        bool isLiteral() const;
        bool isFunction() const;

    private:
        lexer::Lexeme lexeme;
        Node *parent = nullptr;
        std::list<Pointer> children;
    };
}
