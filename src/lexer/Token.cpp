#include <regex>
#include <string>
#include <optional>
#include <pear/lexer/Token.hpp>

namespace pear::lexer {
    Token::Token(Token::Type type, const std::string& description, const std::string& pattern) :
        type(type),
        description(description),
        pattern(std::regex("^" + pattern))
    {
    }
    
    bool Token::match(const std::string& code, std::size_t position, std::string& match) const {
        std::smatch smatch;
        bool result = std::regex_search(code.begin() + position, code.end(), smatch, this->pattern);
        match = smatch.str();
        return result;
    }

    Token::Type Token::getType() const {
        return this->type;
    }
 
    const std::string& Token::getDescription() const {
        return this->description;
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
}

