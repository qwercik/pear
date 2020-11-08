#include <pear/lexer/TokenType.hpp>

namespace pear::lexer {
    const std::unordered_map<TokenType::Identifier, std::string> TokenType::typesNames = {
        { TokenType::NEWLINE, "newline" },
        { TokenType::WHITESPACE, "whitespace" },
        { TokenType::IDENTIFIER, "identifier" },
        { TokenType::LEFT_PARENTHESIS, "left parenthesis" },
        { TokenType::RIGHT_PARENTHESIS, "right parenthesis" },
        { TokenType::COMMA, "comma" },
        { TokenType::INVALID, "invalid token" },
        { TokenType::FLOAT, "floatpoint number" },
        { TokenType::DECIMAL_INTEGER, "decimal integer" },
        { TokenType::STRING, "string" }
    };

    TokenType::TokenType(TokenType::Identifier typeIdentifier) {
        this->typeIdentifier = typeIdentifier;
    }

    TokenType::Identifier TokenType::getIdentifier() const {
        return this->typeIdentifier;
    }

    std::string TokenType::getString() const {
        return TokenType::typesNames.at(this->getIdentifier());
    }

    bool TokenType::operator==(const TokenType& other) const {
        return this->getIdentifier() == other.getIdentifier();
    }
    
    bool TokenType::operator!=(const TokenType& other) const {
        return this->getIdentifier() != other.getIdentifier();
    }
}

