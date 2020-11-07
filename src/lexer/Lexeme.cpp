#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>

namespace pear::lexer {
    Lexeme::Lexeme(TokenType type, const std::string& rawCode, std::size_t position) {
        this->type = type;
        this->rawCode = rawCode;
        this->position = position;
    }

    TokenType Lexeme::getType() const {
        return this->type;
    }

    const std::string& Lexeme::getRawCode() const {
        return this->rawCode;
    }

    std::size_t Lexeme::getPosition() const {
        return this->position;
    }
}

