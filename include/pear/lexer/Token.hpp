#pragma once

#include <string>
#include <regex>
#include <optional>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>

namespace pear::lexer {
    class Token {
    public:
        Token(TokenType type, const std::string& pattern);
        std::optional<Lexeme> match(const std::string& code, std::size_t position, std::size_t lineNumber, std::size_t column) const;

    private:
        TokenType type;
        std::regex pattern;
    };
}

