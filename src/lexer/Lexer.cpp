#include <list>
#include <regex>
#include <pear/lexer/Lexer.hpp>
#include <pear/lexer/LexerException.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/LexemePosition.hpp>
#include <pear/lexer/Token.hpp>

#include <iostream>

namespace pear::lexer {
    Lexer::Lexer(const std::string& code) {
        this->code = code;

        // The priority of rules is important!
        this->tokens = {
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
    }

    std::list<Lexeme> Lexer::run() {
        std::list<Lexeme> lexemes;
        LexemePosition position;

        while (position.getOffset() < this->code.size()) {
            for (const auto& token : this->tokens) {
                std::string match;
                if (token.match(code, position.getOffset(), match)) {
                    auto lexeme = Lexeme(token, match, position);
                    lexeme.updateGlobalLexerPosition(position);
                    lexemes.push_back(lexeme);

                    if (lexeme.getToken().getType() == Token::Type::INVALID) {
                        throw LexerException("Invalid token starting with \'" + lexeme.getContent() + "\'");
                    }
 
                    break;
                }
            }
        }

        return lexemes;
    }
}

