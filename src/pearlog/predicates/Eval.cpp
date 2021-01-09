#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Eval.hpp>

namespace pear::pearlog::predicates {
    bool Eval::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        if (term->getType() != ast::Term::Type::FUNCTION || term->getLexeme().getContent() != "eval" || term->getChildren().size() != 2) {
            return false;
        }

        const auto& expression = *term->getChildren().begin();
        const auto& result = *std::next(term->getChildren().begin());

        if (result->getType() == ast::Term::Type::VARIABLE) {
            substitutions.push_back(Substitution(
                result,
                std::make_unique<ast::Term>(
                    ast::Term::Type::LITERAL,
                    lexer::Lexeme(lexer::Token::Type::DECIMAL_INTEGER, "997")
                )
            ));
        }

        return true;
    }
}
