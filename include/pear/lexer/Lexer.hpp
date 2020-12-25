#pragma once

#include <list>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/Lexeme.hpp>

namespace pear::lexer {
    class Lexer {
    public:
        std::list<Lexeme> run(const std::string& code) const;

    private:
        // The priority is important!
        // TODO: optimize it to be most efficient
        std::list<Token> tokens = {
            Token(Token::Type::NEWLINE, "new line", "\\n"),
            Token(Token::Type::WHITESPACE, "whitespace", "\\s+"),
            Token(Token::Type::LEFT_PARENTHESIS, "left parenthesis", "\\("),
            Token(Token::Type::RIGHT_PARENTHESIS, "right parenthesis", "\\)"),
            Token(Token::Type::COMMA, "comma", ","),
            Token(Token::Type::STRING, "string", "\'[^\']*\'"),
            Token(Token::Type::FLOAT, "float", "[-+]?(?:[1-9][0-9]*|0)\\.[0-9]+"),
            Token(Token::Type::DECIMAL_INTEGER, "decimal integer", "[-+]?(?:[1-9][0-9]*|0)"),
            Token(Token::Type::IDENTIFIER, "identifier", "[a-zA-Z_][0-9a-zA-Z_]*"),
            Token(Token::Type::INVALID, "invalid", ".{1,10}")
        };
    };
}

