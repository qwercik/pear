#pragma once

#include <string>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/LexemePosition.hpp>

namespace pear::lexer {
    class Lexeme {
    public:
        Lexeme(const Token& token, const std::string& content, LexemePosition position);

        const Token& getToken() const;
        const std::string& getContent() const;
        const LexemePosition& getPosition() const;
        std::size_t getLineNumber() const;
        std::size_t getColumn() const;
        
        void updateGlobalLexerPosition(LexemePosition& position) const;

    private:
        Token token;
        std::string content;
        LexemePosition position;
    };
}

