#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/LexemePrinter.hpp>

namespace pear::lexer {
    LexemePrinter::LexemePrinter(const Lexeme& lexeme) :
        lexeme(lexeme)
    {
    }

    void LexemePrinter::print(std::ostream& ostream, const Lexeme& lexeme) {
        switch (lexeme.getToken().getType()) {
            case Token::Type::NEWLINE: ostream << "new line"; break;
            case Token::Type::WHITESPACE: ostream << "whitespace"; break;

            case Token::Type::IDENTIFIER: ostream << "identifier \"" << lexeme.getContent() << "\""; break;
            case Token::Type::DECIMAL_INTEGER: ostream << "decimal integer \"" << lexeme.getContent() << "\""; break;
            case Token::Type::FLOAT: ostream << "float \"" << lexeme.getContent() << "\""; break;
            case Token::Type::STRING: ostream << "string \"" << lexeme.getContent() << "\""; break;

            case Token::Type::LEFT_PARENTHESIS: ostream << "left parenthesis"; break;
            case Token::Type::RIGHT_PARENTHESIS: ostream << "right parenthesis"; break;
            case Token::Type::COMMA: ostream << "comma"; break;

            default: ostream << "invalid token";
        }
    }

    std::ostream& operator<<(std::ostream& stream, const LexemePrinter& lexemePrinter) {
        LexemePrinter::print(stream, lexemePrinter.lexeme);
        return stream;
    }
}