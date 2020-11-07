#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>

namespace pear::lexer {
    Lexeme::Lexeme(TokenType type, const std::string& rawCode, std::size_t position, std::size_t lineNumber, std::size_t column) :
        type(type),
        rawCode(rawCode),
        position(position),
        lineNumber(lineNumber),
        column(column)
    {
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

    std::size_t Lexeme::getLineNumber() const {
        return this->lineNumber;
    }

    std::size_t Lexeme::getColumn() const {
        return this->column;
    }
}

