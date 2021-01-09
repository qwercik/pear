#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/LexemePosition.hpp>

namespace pear::lexer {
    Lexeme::Lexeme(const Token& token, const std::string& content) :
        token(token),
        content(content)
    {
    }

    Lexeme::Lexeme(const Token& token, const std::string& content, LexemePosition position) :
        token(token),
        content(content),
        position(position)
    {
    }
    
    const Token& Lexeme::getToken() const {
        return this->token;
    }

    const std::string& Lexeme::getContent() const {
        return this->content;
    }

    const LexemePosition& Lexeme::getPosition() const {
        return this->position;
    }

    void Lexeme::updateGlobalLexerPosition(LexemePosition& position) const {
        if (this->getToken().getType() == Token::Type::NEWLINE) {
            position.columnNumber = 1;
            position.lineNumber++;
        }

        auto contentSize = this->getContent().size();
        position.columnNumber += contentSize;
        position.offset += contentSize;
    }

    bool Lexeme::operator==(const Lexeme& lexeme) const {
        return this->token == lexeme.token && this->content == lexeme.content;
    }

    bool Lexeme::operator!=(const Lexeme& lexeme) const {
        return !(*this == lexeme);
    }
}

