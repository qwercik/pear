#include <list>
#include <stack>
#include <string>
#include <optional>
#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/parser/ParserException.hpp>
#include <pear/ast/Node.hpp>

namespace pear::parser {
    Parser::Parser(const std::list<lexer::Lexeme>& lexemes) :
        lexemes(lexemes),
        currentNode(&root),
        previousLexeme(nullptr)
    {
    }
    
    void Parser::handleLexeme(const lexer::Lexeme& lexeme) {
        if (lexeme.getType().isScalar()) {
            if (!this->handlingFirstLexeme() && this->previousLexeme->getType().isScalar()) {
                throw ParserException(
                    "Two scalar values cannot lie nerby. "
                    "You have probably missed an operator between them"
                );
            }
        } else if (lexeme.getType() == lexer::TokenType::LEFT_PARENTHESIS) {
            if (this->handlingFirstLexeme() || !this->previousLexeme->getType().isIdentifier()) {
                throw ParserException("Function name should be an identifier");
            }
            
            this->currentNode = this->currentNode->addNextChild(
                new ast::Node(ast::Node::Type::FUNCTION, *this->previousLexeme)
            );
        } else if (lexeme.getType() == lexer::TokenType::RIGHT_PARENTHESIS) {
            if (!this->currentNode->hasParent()) {
                throw ParserException("Redundant right parenthesis");
            }

            this->insertIntoTreeIfScalar(*this->previousLexeme);
            currentNode = currentNode->getParent();
        } else if (lexeme.getType() == lexer::TokenType::COMMA) {
            if (this->handlingFirstLexeme()) {
                throw ParserException("Invalid comma usage");
            }
            
            this->insertIntoTreeIfScalar(*this->previousLexeme);
        }
    }

    bool Parser::handlingFirstLexeme() const {
        return this->previousLexeme == nullptr;
    }

    void Parser::insertIntoTreeIfScalar(const lexer::Lexeme& lexeme) {
        if (lexeme.getType().isIdentifier()) {
            this->currentNode->addNextChild(new ast::Node(ast::Node::Type::VARIABLE, lexeme));
        } else if (lexeme.getType().isLiteral()) {
            this->currentNode->addNextChild(new ast::Node(ast::Node::Type::LITERAL, lexeme));
        }
    }

    ast::AbstractSyntaxTree Parser::run() {
        for (const auto& lexeme : this->lexemes) {
            this->handleLexeme(lexeme);
            this->previousLexeme = &lexeme;
        }
    }
}
