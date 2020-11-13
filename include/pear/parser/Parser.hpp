#pragma once

#include <list>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/AbstractSyntaxTree.hpp>

namespace pear::parser {
    class Parser {
    public:
        Parser(const std::list<lexer::Lexeme>& lexemes);
        ast::AbstractSyntaxTree run();

    private:
        void handlePairOfLexemes(const lexer::Lexeme& predecessor, const lexer::Lexeme& successor);

        std::list<lexer::Lexeme> lexemes;
        ast::AbstractSyntaxTree root;
        ast::Node *current;
    };
}
