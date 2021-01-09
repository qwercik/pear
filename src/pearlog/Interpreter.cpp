#include <pear/pearlog/Interpreter.hpp>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Module.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <pear/pearlog/predicates/True.hpp>
#include <pear/pearlog/predicates/False.hpp>
#include <pear/pearlog/predicates/Eval.hpp>
#include <pear/pearlog/predicates/And.hpp>
#include <pear/pearlog/predicates/Or.hpp>
#include <pear/pearlog/predicates/Print.hpp>
#include <iostream>

namespace pear::pearlog {
    Interpreter::Interpreter() {
        this->predicatesManager.insertBack(std::make_unique<predicates::And>());
        this->predicatesManager.insertBack(std::make_unique<predicates::Or>());
        this->predicatesManager.insertBack(std::make_unique<predicates::Call>());
        this->predicatesManager.insertBack(std::make_unique<predicates::Eval>());
        this->predicatesManager.insertBack(std::make_unique<predicates::Print>());
        this->predicatesManager.insertBack(std::make_unique<predicates::Module>());
        this->predicatesManager.insertBack(std::make_unique<predicates::False>());
        this->predicatesManager.insertBack(std::make_unique<predicates::True>());
    }

    bool Interpreter::execute(const ast::Term::Pointer& term) {
        std::list<Substitution> substitutions;
        auto iterator = this->predicatesManager.getStart();
        return this->execute(iterator, term, substitutions);
    }

    bool Interpreter::execute(PredicatesManager::Iterator& iterator, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) {
        auto termCopy = term->clone();
        for (const auto& substitution : substitutions) {
            substitution.apply(termCopy);
        }

        return this->predicatesManager.executeNext(iterator, *this, termCopy, substitutions);
    }

    PredicatesManager& Interpreter::getPredicatesManager() {
        return this->predicatesManager;
    }
};
