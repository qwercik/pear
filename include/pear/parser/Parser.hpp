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
        bool handlingFirstLexeme() const;
        void handleLexeme(const lexer::Lexeme& lexeme);

        std::list<lexer::Lexeme> lexemes;

        ast::AbstractSyntaxTree root;
        ast::Node *currentNode;
        lexer::Lexeme *previousLexeme;
    };
}
