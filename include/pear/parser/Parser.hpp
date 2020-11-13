#pragma once

#include <list>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::parser {
    class Parser {
    public:
        Parser(const std::list<lexer::Lexeme>& lexemes);
        ast::Term run();

    private:
        std::list<lexer::Lexeme> lexemes;
    };
}
