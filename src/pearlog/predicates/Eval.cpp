#include <iostream>
#include <cmath>
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
        if (!evaluateTree(this->expression, value)) {
            return false;
        }

        if (this->result->getType() == ast::Term::Type::VARIABLE) {

            std::ostringstream oss;
            oss << value;

            this->substitutions.push_back(Substitution(
                this->result,
                std::make_unique<ast::Literal>(lexer::Lexeme(lexer::Token::Type::FLOAT, oss.str()))
            ));

            return true;
        }


        return std::abs(std::stod(this->result->getLexeme().getContent()) - value) < std::numeric_limits<double>::epsilon();
    }


    bool Eval::Instance::evaluateTree(const ast::Term::Pointer& term, double& result) {
        if (term->getType() == ast::Term::Type::LITERAL &&
            (term->getLexeme().getToken().getType() == lexer::Token::Type::FLOAT ||
            term->getLexeme().getToken().getType() == lexer::Token::Type::DECIMAL_INTEGER)) {

            result = std::stod(term->getLexeme().getContent());
            return true;
        } else if (term->getType() == ast::Term::Type::FUNCTION) {
            const auto& name = term->getLexeme().getContent();

            if (term->getChildren().size() == 1 && unaryFunctions.count(name) != 0) {
                auto argument = std::stod(term->getChildren().front()->getLexeme().getContent());
                return unaryFunctions.at(name)(argument, result);
            } else if (leftAssociatedFunctions.count(name) != 0) {
                return evaluateLeftAssociative(term, result, leftAssociatedFunctions.at(name));
            } else if (rightAssociatedFunctions.count(name) != 0) {
                return evaluateRightAssociative(term, result, rightAssociatedFunctions.at(name));
            }
        }

        return false;
    }

    bool Eval::Instance::evaluateLeftAssociative(const ast::Term::Pointer& term, double& result, std::function<bool(double, double, double&)> callback) {
        auto iterator = term->getChildren().begin();
        if (!evaluateTree(*iterator, result)) {
            return false;
        }

        for (iterator++; iterator != term->getChildren().end(); iterator++) {
            double subResult;
            if (!evaluateTree(*iterator, subResult) || !callback(result, subResult, result)) {
                return false;
            }
        }

        return true;
    }

    bool Eval::Instance::evaluateRightAssociative(const ast::Term::Pointer& term, double& result, std::function<bool(double, double, double&)> callback) {
        auto iterator = term->getChildren().rbegin();
        if (!evaluateTree(*iterator, result)) {
            return false;
        }

        for (iterator++; iterator != term->getChildren().rend(); iterator++) {
            double subResult;
            if (!evaluateTree(*iterator, subResult) || !callback(subResult, result, result)) {
                return false;
            }
        }

        return true;
    }


    const std::unordered_map<std::string, std::function<bool(double, double&)>> Eval::Instance::unaryFunctions = {
            {"neg", [](double a, double& result) -> bool { result = -a; return true; }},
            {"abs", [](double a, double& result) -> bool { result = std::fabs(a); return true; }},
            {"radians", [](double a, double& result) -> bool { result = a * M_PI / 180.0; return true; }},
            {"degrees", [](double a, double& result) -> bool { result = a / M_PI * 180.0; return true; }},
            {"sin", [](double a, double& result) -> bool { result = std::sin(a); return true; }},
            {"cos", [](double a, double& result) -> bool { result = std::cos(a); return true; }},
            {"atan", [](double a, double& result) -> bool { result = std::atan(a); return true; }},
            {"tan", [](double a, double& result) -> bool {
                if (std::fmod((result - M_PI / 2), M_PI) < std::numeric_limits<double>::epsilon()) {
                    return false;
                }

                result = std::tan(a);
                return true;
            }},
            {"asin", [](double a, double& result) -> bool {
                if (a < -1 || a > 1) {
                    return false;
                }

                result = std::asin(a);
                return true;
            }},
            {"acos", [](double a, double& result) -> bool {
                if (a < -1 || a > 1) {
                    return false;
                }

                result = std::acos(a);
                return true;
            }}
    };

    const std::unordered_map<std::string, std::function<bool(double, double, double&)>> Eval::Instance::leftAssociatedFunctions = {
            {"add", [](double a, double b, double& result) -> bool { result = a + b; return true; }},
            {"sub", [](double a, double b, double& result) -> bool { result = a - b; return true; }},
            {"mul", [](double a, double b, double& result) -> bool { result = a * b; return true; }},
            {"div", [](double a, double b, double& result) -> bool { result = a / b; return true; }},
            {"mod", [](double a, double b, double& result) -> bool { result = std::fmod(a, b); return true; }}
    };

    const std::unordered_map<std::string, std::function<bool(double, double, double&)>> Eval::Instance::rightAssociatedFunctions = {
            {"pow", [](double a, double b, double& result) -> bool { result = std::pow(a, b); return true; }}
    };
}
