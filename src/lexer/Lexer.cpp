#include <list>
#include <regex>
#include <pear/lexer/Lexer.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/TokenType.hpp>

#include <iostream>

namespace pear::lexer {
    Lexer::Lexer(const std::string& code) {
        this->code = code;
        this->tokens = {
            Token(TokenType::WHITESPACE, "\\s+"),
            Token(TokenType::LEFT_PARENTHESIS, "\\("),
            Token(TokenType::RIGHT_PARENTHESIS, "\\)"),
            Token(TokenType::COMMA, ","),
            Token(TokenType::DECIMAL_NUMBER, "[-+]?[1-9][0-9]*"),
            Token(TokenType::STRING, "\'[^\']*\'"),
            Token(TokenType::IDENTIFIER, "[a-zA-Z][0-9a-zA-Z]*"),
            Token(TokenType::INVALID, ".")
        };
    }

    std::list<Lexeme> Lexer::run() {
        std::list<Lexeme> lexemes;

        std::size_t index = 0;
        while (index < this->code.size()) {
            for (const auto& token : this->tokens) {
                auto matched = token.match(code, index);
                if (matched) {
                    lexemes.push_back(*matched);
                    index += (*matched).getRawCode().size();
                    break;
                }
            }
        }

        return lexemes;
    }
}
