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

        // The priority of rules is important!
        this->tokens = {
            Token(TokenType::NEWLINE, "\\n"),
            Token(TokenType::WHITESPACE, "\\s+"),
            Token(TokenType::LEFT_PARENTHESIS, "\\("),
            Token(TokenType::RIGHT_PARENTHESIS, "\\)"),
            Token(TokenType::COMMA, ","),
            Token(TokenType::STRING, "\'[^\']*\'"),
            Token(TokenType::FLOAT, "[-+]?(?:[1-9][0-9]*|0)\\.[0-9]+"),
            Token(TokenType::DECIMAL_INTEGER, "[-+]?(?:[1-9][0-9]*|0)"),
            Token(TokenType::IDENTIFIER, "[a-zA-Z_][0-9a-zA-Z_]*"),
            Token(TokenType::INVALID, ".")
        };
    }

    std::list<Lexeme> Lexer::run() {
        std::list<Lexeme> lexemes;

        std::size_t index = 0;
        std::size_t lineNumber = 1;
        std::size_t column = 1;

        while (index < this->code.size()) {
            for (const auto& token : this->tokens) {
                auto matched = token.match(code, index, lineNumber, column);
                if (matched) {
                    auto lexeme = *matched;

                    lexemes.push_back(lexeme);
                    auto lexemeSize = lexeme.getRawCode().size();
                    index += lexemeSize;
                    column += lexemeSize;

                    if (lexeme.getType() == TokenType::NEWLINE) {
                        lineNumber++;
                        column = 1;
                    }
 
                    break;
                }
            }
        }

        return lexemes;
    }
}
