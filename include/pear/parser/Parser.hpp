#pragma once

#include <list>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::parser {
    class Parser {
    public:
        Parser(const std::list<lexer::Lexeme>& lexemes);
        ast::Term::Pointer run();

    private:
        void handleLexeme(const lexer::Lexeme& lexeme);

        std::list<lexer::Lexeme> lexemes;
        ast::Term::Pointer root;
        ast::Term *current;
        lexer::Lexeme *previousLexeme;
    };
}
