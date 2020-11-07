#pragma once

#include <list>
#include <pear/lexer/Token.hpp>
#include <pear/lexer/Lexeme.hpp>

namespace pear::lexer {
    class Lexer {
    public:
        Lexer(const std::string& code);
        std::list<Lexeme> run();

    private:
        std::list<Token> tokens;
        std::string code;
    };
}

