#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/Eval.hpp>

namespace pear::pearlog::predicates {
    bool Eval::execute(const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        if (term->getType() != ast::Term::Type::FUNCTION || term->getLexeme().getContent() != "eval" || term->getChildren().size() != 2) {
            return false;
        }

        const auto& expression = *term->getChildren().begin();
        const auto& result = *std::next(term->getChildren().begin());

        if (result->getType() == ast::Term::Type::VARIABLE) {
            substitutions.push_back(
                Substitution(
                    result,
                    Term(
                        ast::Term::Type::LITERAL,
                        lexer::Lexeme(
                            lexer::tokens::TI
                        )
                    )
                )
            );
        }

        return true;
    }
}
