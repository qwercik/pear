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
            for (const auto& [tokenType, pattern] : this->tokensRegexes) {
                std::regex regex("^" + pattern);
                std::smatch match;
                if (std::regex_search(code.begin() + position.getOffset(), code.end(), match, regex)) {
                    if (tokenType == Token::Type::INVALID) {
                        throw LexerException("Invalid token starting with \'" + match.str() + "\'");
                    }

                    auto lexeme = Lexeme(Token(tokenType), match.str(), position);
                    lexeme.updateGlobalLexerPosition(position);
                    lexemes.push_back(lexeme);
                    break;
                }
            }
        }

        return lexemes;
    }
}

