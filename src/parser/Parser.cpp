#include <list>
#include <stack>
#include <string>
#include <optional>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/parser/ParserException.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Literal.hpp>

namespace pear::parser {
    Parser::Parser(const std::list<lexer::Lexeme>& lexemes) :
        lexemes(lexemes)
    {
    }

    ast::Term Parser::run() {
        std::optional<ast::Term> currentTerm;
        std::stack<ast::Function> functions;

        for (auto it = this->lexemes.begin(); it != this->lexemes.end(); it++) {
            const auto& lexeme = *it;
            auto lexemeType = lexeme.getType();

            if (lexemeType.isIdentifier() || lexemeType.isLiteral()) {
                if (currentTerm.has_value()) {
                    throw ParserException(
                        "two scalar (identifier or literal) values cannot lie nearby - you have probably missed "
                        "a comma or parenthesis between them"
                    );
                } else if (lexemeType.isIdentifier()) {
                    // Should I check whether nextLexeme exist?
                    auto nextLexeme = *std::next(it);
                    if (nextLexeme.getType() == lexer::TokenType::LEFT_PARENTHESIS) {
                        currentTerm = ast::Function(lexeme.getRawCode()); // TODO: rename getRawCode() with getContent()
                    } else {
                        currentTerm = ast::Variable(lexeme.getRawCode());
                    }
                } else if (lexemeType == lexer::TokenType::STRING) {
                    currentTerm = ast::Literal<std::string>(lexeme.getRawCode());
                } else if (lexemeType == lexer::TokenType::DECIMAL_INTEGER) {
                    currentTerm = ast::Literal<long long>(std::stoll(lexeme.getRawCode())); // TODO: implement big ints
                } else if (lexemeType == lexer::TokenType::FLOAT) {
                    currentTerm = ast::Literal<long double>(std::stold(lexeme.getRawCode())); // TODO: implement bit floats
                }
            } else if (lexemeType == lexer::TokenType::LEFT_PARENTHESIS) {
                functions.push(currentTerm);
                currentTerm = std::nullopt;
            } else if (lexemeType == lexer::TokenType::COMMA || lexemeType == lexer::TokenType::RIGHT_PARENTHESIS) {
                if (functions.empty()) {
                    throw ParserException("neither comma nor right parenthesis cannot be used outside any function definition");
                }

                if (!currentTerm.has_value()) {
                    throw ParserException("no argument");
                }

                functions.top().addArgument(*currentTerm);
                currentTerm = std::nullopt;

                if (lexemeType == lexer::TokenType::RIGHT_PARENTHESIS) {
                    currentTerm = functions.top();
                    functions.pop();
                }
            }
        }

        if (!currentTerm.has_variable) {
            throw ParserException("strange error");
        }

        return *currentTerm;
    }
}
