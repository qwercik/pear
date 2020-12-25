#pragma once

#include <string>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/LexemePosition.hpp>

namespace pear::lexer {
    class Lexeme {
    public:
        Lexeme() = default;
        Lexeme(const Token *token, const std::string& content, LexemePosition position);

        const Token *getToken() const;
        const std::string& getContent() const;
        const LexemePosition& getPosition() const;

        void updateGlobalLexerPosition(LexemePosition& position) const;

    private:
        const Token * const token;
        std::string content;
        LexemePosition position;
    };
}

