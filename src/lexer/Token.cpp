#include <regex>
#include <string>
#include <optional>
#include <pear/lexer/Token.hpp>

namespace pear::lexer {
    Token::Token(Token::Type type) :
        type(type)
    {
    }

    Token::Type Token::getType() const {
        return this->type;
    }

    bool Token::isWhitespace() const {
        return this->type == Type::WHITESPACE || this->type == Type::NEWLINE;
    }

    bool Token::isIdentifier() const {
        return this->type == Type::IDENTIFIER;
    }

    bool Token::isLiteral() const {
        auto whitelist = {Type::DECIMAL_INTEGER, Type::FLOAT, Type::STRING};
        return std::find(std::begin(whitelist), std::end(whitelist), this->type) != std::end(whitelist);
    }

    bool Token::isScalar() const {
        return this->isIdentifier() || this->isLiteral();
    }

    bool Token::isOperator() const {
        auto whitelist = {Type::LEFT_PARENTHESIS, Type::RIGHT_PARENTHESIS, Type::COMMA};
        return std::find(std::begin(whitelist), std::end(whitelist), this->type) != std::end(whitelist);
    }

    bool Token::operator==(const Token& token) const {
        return this->type == token.type;
    }

    bool Token::operator!=(const Token& token) const {
        return !(*this == token);
    }
}

