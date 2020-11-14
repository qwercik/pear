#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/parser/ParserException.hpp>
#include <pear/ast/Node.hpp>
#include <iostream>

namespace pear::parser {
    Parser::Parser(const std::list<lexer::Lexeme>& lexemes) :
        lexemes(lexemes),
        current(&root),
        previousLexeme(nullptr)
    {
    }

    ast::Tree Parser::run() {
        if (!lexemes.front().getType().isIdentifier()) {
            throw ParserException("First token should always be an identifier");
        }
        previousLexeme = &lexemes.front();

        for (auto it = std::next(this->lexemes.begin()); it != this->lexemes.end(); it++) {
            if (!it->getType().isWhitespace()) {
                handleLexeme(*it);
                previousLexeme = &*it;
            }
        }

        return this->root;
    }

    void Parser::handleLexeme(const lexer::Lexeme& currentLexeme) {
        auto currentLexemeType = currentLexeme.getType();
        auto previousLexemeType = this->previousLexeme->getType();
    
        if (currentLexemeType.isScalar() && previousLexemeType.isScalar()) {
            throw ParserException("scalar near by scalar");
        } else if (currentLexemeType == lexer::TokenType::LEFT_PARENTHESIS) {
            if (!previousLexemeType.isIdentifier()) {
                throw ParserException("wystąpił błąd");
            }

            current = current->addNextChild(new ast::Node(ast::Node::Type::FUNCTION, *previousLexeme));
        } else if (currentLexemeType == lexer::TokenType::RIGHT_PARENTHESIS) {
            if (!current->hasParent()) {
                throw ParserException("hasParent");
            } else if (previousLexemeType == lexer::TokenType::COMMA) {
                throw ParserException("comma before right parenthesis");
            } else if (previousLexemeType == lexer::TokenType::IDENTIFIER) {
                current->addNextChild(new ast::Node(ast::Node::Type::VARIABLE, *previousLexeme));
            } else if (previousLexemeType.isLiteral()) {
                current->addNextChild(new ast::Node(ast::Node::Type::LITERAL, *previousLexeme));
            }
 
            current = current->getParent();
        } else if (currentLexemeType == lexer::TokenType::COMMA) {
            if (previousLexemeType == lexer::TokenType::COMMA) {
                throw ParserException("comma before comma");
            } else if (previousLexemeType == lexer::TokenType::LEFT_PARENTHESIS) {
                throw ParserException("left parenthesis befor comma");
            } else if (previousLexemeType == lexer::TokenType::IDENTIFIER) {
                current->addNextChild(new ast::Node(ast::Node::Type::VARIABLE, *previousLexeme));
            } else if (previousLexemeType.isLiteral()) {
                current->addNextChild(new ast::Node(ast::Node::Type::LITERAL, *previousLexeme));
            }
        }
    }
}
