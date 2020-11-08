#include <list>
#include <stack>
#include <optional>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Literal.hpp>

namespace pear::parser {
    Parser::Parser(const std::list<Lexeme>& lexemes) :
        lexemes(lexemes)
    {
    }

    std::list<Term> Parser::run() {
        std::optional<Lexeme> currentTerm;
        std::stack<Lexeme> functions;

        for (const auto& lexeme : this->lexemes) {
            auto lexemeType = lexeme.getType();

            if (lexemeType.isIdentifier() || lexemeType.isLiteral()) {
                if (currentTerm.has_value()) {
                    // Error: two scalars nearby
                } else {
                    currentTerm = lexeme;
                }
            } else if (lexemeType == lexer::TokenType::LEFT_PARENTHESIS) {
                if (currentTerm.has_value()) {
                    if (currentTerm.getType().isIdentifier()) {
                        functions.push(Function(currentTerm.getRawCode()));
                        currentTerm = std::nullopt;
                    } else {
                        // Error: literal must not be a function identifier
                    }
                } else {
                    // Error
                }
            } else if (lexemeType == lexer::TokenType::COMMA) {
                if (functions.empty()) {
                    // Error
                } else {
                    functions.top().addArgument(currentTerm);
                    currentTerm = std::nullopt;
                }
            } else if (lexemeType == lexer::TokenType::RIGHT_PARENTHESIS) {
                if (functions.empty()) {
                    // Error
                } else {
                    currentTerm = functions.top();
                    functions.pop();
                }
            }
        }
    }
}
