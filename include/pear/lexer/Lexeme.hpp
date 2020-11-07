#pragma once

#include <string>
#include <pear/lexer/TokenType.hpp>

namespace pear::lexer {
    class Lexeme {
    public:
        Lexeme(TokenType type, const std::string& rawCode, std::size_t position, std::size_t lineNumber, std::size_t column);
        
        TokenType getType() const;
        const std::string& getRawCode() const;
        std::size_t getPosition() const;
        std::size_t getLineNumber() const;
        std::size_t getColumn() const;
        
    private:
        TokenType type;
        std::string rawCode;
        std::size_t position;
        std::size_t lineNumber;
        std::size_t column;
    };
}

