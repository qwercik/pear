#pragma once

#include <string>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/LexemePosition.hpp>

namespace pear::lexer {
    class Lexeme {
    public:
        Lexeme() = default;
        Lexeme(const Lexeme& lexeme) = default;
        Lexeme(const Token *token, const std::string& content, LexemePosition position);
        Lexeme& operator=(const Lexeme& lexeme) = default;

        const Token *getToken() const;
        const std::string& getContent() const;
        const LexemePosition& getPosition() const;

        void updateGlobalLexerPosition(LexemePosition& position) const;

    private:
        const Token * token = nullptr;
        std::string content;
        LexemePosition position;
    };
}

