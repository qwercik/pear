#pragma once

#include <memory>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Node {
    public:
        using NodePointer = Node*;
        using ChildNodePointer = std::unique_ptr<Node>;
        using ChildrenList = std::list<ChildNodePointer>;

        enum class Type {
            VARIABLE,
            FUNCTION,
            LITERAL
        };

        Node(Type type, const lexer::Lexeme& lexeme);
        
        Type getType() const;
        const lexer::Lexeme& getLexeme() const;
        NodePointer getParent() const;
        bool hasParent() const;
        const ChildrenList& getChildren() const;

        NodePointer addNextChild(ChildNodePointer child);

    private:
        Type type;
        lexer::Lexeme lexeme;
        NodePointer parent;
        ChildrenList children;
    };
}
