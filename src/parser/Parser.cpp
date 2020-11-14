#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <pear/lexer/Lexeme.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/parser/ParserException.hpp>
#include <pear/ast/Node.hpp>
#include <iostream>

namespace pear::parser {
    Parser::Parser(const std::list<lexer::Lexeme>& lexemes) :
        lexemes(lexemes),
        root(std::make_shared<ast::Node>()),
        current(root.get()),
        previousLexeme(nullptr)
    {
    }

    std::shared_ptr<ast::Node> Parser::run() {
        if (!lexemes.front().getToken().isIdentifier()) {
            throw ParserException("First token should always be an identifier");
        }
        previousLexeme = &lexemes.front();

        for (auto it = std::next(this->lexemes.begin()); it != this->lexemes.end(); it++) {
            if (!it->getToken().isWhitespace()) {
                handleLexeme(*it);
                previousLexeme = &*it;
            }
        }

        return this->root;
    }

    void Parser::handleLexeme(const lexer::Lexeme& currentLexeme) {
        auto currentToken = currentLexeme.getToken();
        auto previousToken = this->previousLexeme->getToken();
    
        if (currentToken.isScalar() && previousToken.isScalar()) {
            throw ParserException("scalar near by scalar");
        } else if (currentToken.getType() == lexer::Token::Type::LEFT_PARENTHESIS) {
            if (!previousToken.isIdentifier()) {
                throw ParserException("wystąpił błąd");
            }

            current = current->addNextChild(new ast::Node(*previousLexeme));
        } else if (currentToken.getType() == lexer::Token::Type::RIGHT_PARENTHESIS) {
            if (!current->hasParent()) {
                throw ParserException("hasParent");
            } else if (previousToken.getType() == lexer::Token::Type::COMMA) {
                throw ParserException("comma before right parenthesis");
            } else if (previousToken.isScalar()) {
                current->addNextChild(new ast::Node(*previousLexeme));
            }
 
            current = current->getParent();
        } else if (currentToken.getType() == lexer::Token::Type::COMMA) {
            if (previousToken.getType() == lexer::Token::Type::COMMA) {
                throw ParserException("comma before comma");
            } else if (previousToken.getType() == lexer::Token::Type::LEFT_PARENTHESIS) {
                throw ParserException("left parenthesis befor comma");
            } else if (previousToken.isScalar()) {
                current->addNextChild(new ast::Node(*previousLexeme));
            }
        }
    }
}

