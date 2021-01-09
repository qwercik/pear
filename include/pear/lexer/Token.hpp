#pragma once

#include <string>
#include <regex>

namespace pear::lexer {
    class Token {
    public:
        enum class Type {
            // Whitespace characters (newline has the greatest priority)
            NEWLINE,
            WHITESPACE,

            // Scalars
            IDENTIFIER,
            DECIMAL_INTEGER,
            FLOAT,
            STRING,

            // Operators
            LEFT_PARENTHESIS,
            RIGHT_PARENTHESIS,
            COMMA,

            INVALID
        };

        Token(Type type);
        Token(const Token& token) = default;

        Type getType() const;
        bool isWhitespace() const;
        bool isIdentifier() const;
        bool isLiteral() const;
        bool isScalar() const;
        bool isOperator() const;

        bool operator==(const Token& token) const;
        bool operator!=(const Token& token) const;

    private:
        Type type;
    };
}

