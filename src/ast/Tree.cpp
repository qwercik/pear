#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Tree.hpp>

namespace pear::ast {
    Tree::Tree() :
        Node(Type::FUNCTION, lexer::Lexeme(lexer::TokenType::IDENTIFIER, "code", 0, 0, 0))
    {
    }
}

