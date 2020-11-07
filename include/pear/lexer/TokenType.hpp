#pragma once

#include <string>
#include <unordered_map>

namespace pear::lexer {
    class TokenType {
    public:
        enum Identifier {
            NEWLINE,
            WHITESPACE,
            IDENTIFIER,
            LEFT_PARENTHESIS,
            RIGHT_PARENTHESIS,
            COMMA,
            INVALID,
            DECIMAL_NUMBER,
            STRING
        };

        TokenType(Identifier typeIdentifier);

        Identifier getIdentifier() const;
        std::string getString() const;
        
        bool operator==(const TokenType& other) const;
        bool operator!=(const TokenType& other) const;

    private:
        static const std::unordered_map<Identifier, std::string> typesNames;
        Identifier typeIdentifier;
    };
}

