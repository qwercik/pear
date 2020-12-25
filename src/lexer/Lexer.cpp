#include <list>
#include <regex>
#include <pear/lexer/Lexer.hpp>
#include <pear/lexer/LexerException.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/LexemePosition.hpp>
#include <pear/lexer/Token.hpp>

#include <iostream>

namespace pear::lexer {
    std::list<Lexeme> Lexer::run(const std::string& code) const {
        std::list<Lexeme> lexemes;
        LexemePosition position;

        while (position.getOffset() < code.size()) {
            for (const auto& token : this->tokens) {
                std::string match;
                if (token.match(code, position.getOffset(), match)) {
                    if (token.getType() == Token::Type::INVALID) {
                        throw LexerException("Invalid token starting with \'" + match + "\'");
                    }

                    auto lexeme = Lexeme(&token, match, position);
                    lexeme.updateGlobalLexerPosition(position);
                    lexemes.push_back(lexeme);
                    break;
                }
            }
        }

        return lexemes;
    }
}

