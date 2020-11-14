#pragma once

#include <list>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Tree.hpp>

namespace pear::parser {
    class Parser {
    public:
        Parser(const std::list<lexer::Lexeme>& lexemes);
        ast::Tree run();

    private:
        void handleLexeme(const lexer::Lexeme& lexeme);

        std::list<lexer::Lexeme> lexemes;
        ast::Tree root;
        ast::Node *current;
        lexer::Lexeme *previousLexeme;
    };
}
