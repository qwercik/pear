#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/Literal.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/Eval.hpp>

namespace pear::pearlog::predicates {
    Eval::Eval(Interpreter& interpreter) :
            BuiltinPredicate(interpreter)
    {
    }

    bool Eval::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION && term->getLexeme().getContent() == "eval" && term->getChildren().size() == 2;
    }

    std::unique_ptr<Predicate::Instance> Eval::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<Eval::Instance>(term);
    }

    Eval::Instance::Instance(const ast::Term::Pointer& term) :
        expression(term->getChildren().front()->clone()),
        result((*std::next(term->getChildren().begin()))->clone())
    {
    }

    bool Eval::Instance::next() {
        if (this->alreadyCalled) {
            return false;
        }
        this->alreadyCalled = true;

        double value;
        evaluateTree(this->expression, value);

        if (this->result->getType() == ast::Term::Type::VARIABLE) {
            this->substitutions.push_back(Substitution(
                this->result,
                std::make_unique<ast::Literal>(lexer::Lexeme(lexer::Token::Type::FLOAT, std::to_string(value)))
            ));

            return true;
        }


        return this->result->getLexeme().getContent() == std::to_string(value);
    }


    bool Eval::Instance::evaluateTree(const ast::Term::Pointer& term, double& result) {
        if (term->getType() == ast::Term::Type::LITERAL &&
            (term->getLexeme().getToken().getType() == lexer::Token::Type::FLOAT ||
            term->getLexeme().getToken().getType() == lexer::Token::Type::DECIMAL_INTEGER)) {

            result = std::stod(term->getLexeme().getContent());
        } else if (term->getType() == ast::Term::Type::FUNCTION) {
            const auto &name = term->getLexeme().getContent();

            if (name == "add") {
                for (const auto &child : term->getChildren()) {
                    double subResult = 0;
                    evaluateTree(child, subResult);
                    result += subResult;
                }

                return true;
            }
        }

        return false;
    }
}
