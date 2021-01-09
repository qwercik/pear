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
        const std::list<std::pair<Token::Type, std::string>> tokensRegexes = {
                {Token::Type::NEWLINE, "\\n"},
                {Token::Type::WHITESPACE, "\\s+"},
                {Token::Type::LEFT_PARENTHESIS, "\\("},
                {Token::Type::RIGHT_PARENTHESIS, "\\)"},
                {Token::Type::COMMA, ","},
                {Token::Type::STRING, R"('[^']*')"},
                {Token::Type::FLOAT, "[-+]?(?:[1-9][0-9]*|0)\\.[0-9]+"},
                {Token::Type::DECIMAL_INTEGER, "[-+]?(?:[1-9][0-9]*|0)"},
                {Token::Type::IDENTIFIER, "[a-zA-Z_][0-9a-zA-Z_]*"},
                {Token::Type::INVALID, ".{1,10}"}
        };
    };
}

