#include <regex>
#include <optional>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/lexer/Lexeme.hpp>

namespace pear::lexer {
    Token::Token(TokenType type, const std::string& pattern) :
        type(type),
        pattern(std::regex("^" + pattern))
    {
    }

    std::optional<Lexeme> Token::match(const std::string& code, std::size_t position, std::size_t lineNumber, std::size_t column) const {
        std::smatch regex_match;

        if (std::regex_search(code.begin() + position, code.end(), regex_match, this->pattern)) {
            return Lexeme(this->type, regex_match.str(), position, lineNumber, column);
        } else {
            return std::nullopt;
        }
    }
}

