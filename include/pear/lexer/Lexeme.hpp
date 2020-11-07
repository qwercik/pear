#pragma once

#include <string>
#include <pear/lexer/TokenType.hpp>

namespace pear::lexer {
    class Lexeme {
    public:
        Lexeme(TokenType type, const std::string& rawCode, std::size_t position);
        
        TokenType getType() const;
        const std::string& getRawCode() const;
        std::size_t getPosition() const;
        
    private:
        TokenType type;
        std::string rawCode;
        std::size_t position;
    };
}

