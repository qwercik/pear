#pragma once

namespace pear::lexer {
    enum class TokenType {
        WHITESPACE,
        IDENTIFIER,
        LEFT_PARENTHESIS,
        RIGHT_PARENTHESIS,
        COMMA,
        INVALID,
        DECIMAL_NUMBER,
        STRING
    };
}

