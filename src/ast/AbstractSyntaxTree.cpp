#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/AbstractSyntaxTree.hpp>

namespace pear::ast {
    AbstractSyntaxTree::AbstractSyntaxTree() :
        Node(Type::FUNCTION, lexer::Lexeme(lexer::TokenType::IDENTIFIER, "code", 0, 0, 0))
    {
    }
}

