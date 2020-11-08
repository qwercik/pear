#pragma once

#include <list>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::parser {
    class Parser {
    public:
        Parser(const std::list<Lexeme>& lexemes);
        std::list<Term> run();

    private:
        std::list<Lexeme> lexemes;
    };
}
