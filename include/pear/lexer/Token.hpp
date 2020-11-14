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

        Token(Type type, const std::string& description, const std::string& pattern);

        bool match(const std::string& code, std::size_t position, std::string& match) const;

        Type getType() const; 
        bool isWhitespace() const;
        bool isIdentifier() const;
        bool isLiteral() const;
        bool isScalar() const;
        bool isOperator() const;

        const std::string& getDescription() const;

    private:
        Type type;
        std::regex pattern;
        std::string description;
    };
}

