#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/parser/ParserException.hpp>
#include <pear/ast/Node.hpp>

template <typename Iterator, typename Function>
void iterateOverAdjacentPairs(Iterator start, Iterator end, Function callback) {
    if (start != end) {
        Iterator predecessor = start;
        Iterator successor = std::next(predecessor);

        for (; successor != end; predecessor++, successor++) {
            callback(*predecessor, *successor);
        }
    }
}


namespace pear::parser {
    Parser::Parser(const std::list<lexer::Lexeme>& lexemes) :
        lexemes(lexemes),
        current(&root)
    {
    }

    ast::AbstractSyntaxTree Parser::run() {
        iterateOverAdjacentPairs(
            std::begin(this->lexemes),
            std::end(this->lexemes),
            [&](const lexer::Lexeme& predecessor, const lexer::Lexeme& successor) {
                if (!predecessor.getType().isWhitespace() && !successor.getType().isWhitespace()) {
                    std::cout << predecessor.getRawCode() << " " << successor.getRawCode() << std::endl;
                    this->handlePairOfLexemes(predecessor, successor);
                }
            }
        );

        return this->root;
    }
    
    void Parser::handlePairOfLexemes(const lexer::Lexeme& predecessor, const lexer::Lexeme& successor) {
        // TODO: filter whitespaces
        auto predecessorType = predecessor.getType();
        auto successorType = successor.getType();

        if (predecessorType.isIdentifier()) {
            if (successorType.isScalar()) {
                throw ParserException("ID SC");
            } else if (successorType == lexer::TokenType::COMMA) {
                // Trzeba dodać nową zmienną z leksemem predecessor
                // Należy przy tym sprawdzić, czy znajdujemy się wewnątrz jakiejś funkcji
                // Inaczej należy wyrzucić błąd
                if (current == &root) {
                    throw ParserException("Not inside function");
                }

                current->addNextChild(new ast::Node(ast::Node::Type::VARIABLE, predecessor));
            } else if (successorType == lexer::TokenType::LEFT_PARENTHESIS) {
                // Trzeba dodać nową funkcję z leksemem predecessor
                current = current->addNextChild(new ast::Node(ast::Node::Type::FUNCTION, predecessor));
            } else if (successorType == lexer::TokenType::RIGHT_PARENTHESIS) {
                // Trzeba dodać nową zmienną z leksemem predecessor
                // Należy przy tym sprawdzić, czy znajdujemy się wewnątrz jakiejś funkcji
                // Inaczej należy wyrzucić błąd
                if (!current->hasParent()) {
                    throw ParserException("Not inside function");
                }

                current->addNextChild(new ast::Node(ast::Node::Type::VARIABLE, predecessor));

                // Poza tym należy wrócić do funkcji rodzica
                current = current->getParent();
            }
        } else if (predecessorType.isLiteral()) {
            if (successorType.isScalar()) {
                throw ParserException("LT SC");
            } else if (successorType == lexer::TokenType::COMMA) {
                // Trzeba dodać literał z leksemem predecessor
                // Należy przy tym sprawdzić, czy znajdujemy się wewnątrz jakiejś funkcji
                // Inaczej należy wyrzucić błąd
                if (!current->hasParent()) {
                    throw ParserException("Not inside function");
                }

                current->addNextChild(new ast::Node(ast::Node::Type::LITERAL, predecessor));
            } else if (successorType == lexer::TokenType::LEFT_PARENTHESIS) {
                throw ParserException("LT LP");
            } else if (successorType == lexer::TokenType::RIGHT_PARENTHESIS) {
                // Trzeba dodać literał z leksemem predecessor
                // Należy przy tym sprawdzić, czy znajdujemy się wewnątrz jakiejś funkcji
                // Inaczej należy wyrzucić błąd
                if (!current->hasParent()) {
                    throw ParserException("Not inside function");
                }

                current->addNextChild(new ast::Node(ast::Node::Type::LITERAL, predecessor));

                // Poza tym, należy wrócić do funkcji rodzica
                current = current->getParent();
            }
        } else if (predecessorType == lexer::TokenType::COMMA) {
            if (successorType == lexer::TokenType::COMMA) {
                throw ParserException("CM CM");
            } else if (successorType == lexer::TokenType::LEFT_PARENTHESIS) {
                throw ParserException("CM LP");
            } else if (successorType == lexer::TokenType::RIGHT_PARENTHESIS) {
                throw ParserException("CM RP");
            }
        } else if (predecessorType == lexer::TokenType::LEFT_PARENTHESIS) {
            if (successorType == lexer::TokenType::COMMA) {
                throw ParserException("LP CM");
            } else if (successorType == lexer::TokenType::LEFT_PARENTHESIS) {
                throw ParserException("LP LP");
            } else if (successorType == lexer::TokenType::RIGHT_PARENTHESIS) {
                // Trzeba wrócić do funkcji rodzica
                if (!current->hasParent()) {
                    throw ParserException("Not inside function");
                }
                current = current->getParent();
            }
        } else if (predecessorType == lexer::TokenType::RIGHT_PARENTHESIS) {
            if (successorType.isScalar()) {
                throw ParserException("RP SC");
            } else if (successorType == lexer::TokenType::LEFT_PARENTHESIS) {
                throw ParserException("RP LP");
            } else if (successorType == lexer::TokenType::RIGHT_PARENTHESIS) {
                // Trzeba wrócić do funkcji rodzica
                if (!current->hasParent()) {
                    throw ParserException("Not inside function");
                }
                current = current->getParent();
            }
        }
    }
}
