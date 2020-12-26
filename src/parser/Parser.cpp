#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <pear/lexer/Lexeme.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/parser/ParserException.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Literal.hpp>

namespace pear::parser {
    Parser::Parser(const std::list<lexer::Lexeme>& lexemes) :
        lexemes(lexemes),
        current(nullptr),
        previousLexeme(nullptr)
    {
    }

    ast::Term::Pointer Parser::run() {
        if (!lexemes.front().getToken()->isIdentifier()) {
            throw ParserException("First token should always be an identifier");
        }
        previousLexeme = &lexemes.front();
        root = std::make_unique<ast::Function>(*previousLexeme);
        current = root.get();

        for (auto it = std::next(this->lexemes.begin()); it != this->lexemes.end(); it++) {
            if (!it->getToken()->isWhitespace()) {
                handleLexeme(*it);
                previousLexeme = &*it;
            }
        }

        return std::move(this->root->moveChildren().front());
    }

    void Parser::handleLexeme(const lexer::Lexeme& currentLexeme) {
        auto currentToken = currentLexeme.getToken();
        auto previousToken = this->previousLexeme->getToken();

        if (currentToken->isScalar() && previousToken->isScalar()) {
            throw ParserException("scalar near by scalar");
        } else if (currentToken->getType() == lexer::Token::Type::LEFT_PARENTHESIS) {
            if (!previousToken->isIdentifier()) {
                throw ParserException("wystąpił błąd");
            }

            current = current->addNextChild(std::make_unique<ast::Function>(*previousLexeme));
        } else if (currentToken->getType() == lexer::Token::Type::RIGHT_PARENTHESIS) {
            if (!current->hasParent()) {
                throw ParserException("hasParent");
            } else if (previousToken->getType() == lexer::Token::Type::COMMA) {
                throw ParserException("comma before right parenthesis");
            } else if (previousToken->isLiteral()) {
                current->addNextChild(std::make_unique<ast::Literal>(*previousLexeme));
            } else if (previousToken->isIdentifier()) {
                current->addNextChild(std::make_unique<ast::Variable>(*previousLexeme));
            }
 
            current = current->getParent();
        } else if (currentToken->getType() == lexer::Token::Type::COMMA) {
            if (previousToken->getType() == lexer::Token::Type::COMMA) {
                throw ParserException("comma before comma");
            } else if (previousToken->getType() == lexer::Token::Type::LEFT_PARENTHESIS) {
                throw ParserException("left parenthesis befor comma");
            } else if (previousToken->isLiteral()) {
                current->addNextChild(std::make_unique<ast::Literal>(*previousLexeme));
            } else if (previousToken->isIdentifier()) {
                current->addNextChild(std::make_unique<ast::Variable>(*previousLexeme));
            }
        }
    }
}

