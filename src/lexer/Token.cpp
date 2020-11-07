#include <regex>
#include <optional>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/lexer/Lexeme.hpp>

namespace pear::lexer {
    Token::Token(TokenType type, const std::string& pattern) {
        this->type = type;
        this->pattern = std::regex("^" + pattern);
    }

    std::optional<Lexeme> Token::match(const std::string& code, std::size_t position) const {
        std::smatch regex_match;

        if (std::regex_search(code.begin() + position, code.end(), regex_match, this->pattern)) {
            return Lexeme(this->type, regex_match.str(), position);
        } else {
            return std::nullopt;
        }
    }
}

