#include <pear/pearlog/Interpreter.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Function.hpp>
#include <pear/pearlog/predicates/Module.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <pear/pearlog/predicates/True.hpp>
#include <pear/pearlog/predicates/False.hpp>
#include <pear/pearlog/predicates/And.hpp>
#include <pear/pearlog/predicates/Or.hpp>
#include <pear/pearlog/predicates/Print.hpp>
#include <iostream>
#include <pear/pearlog/predicates/Unify.hpp>

namespace pear::pearlog {
    Interpreter::Interpreter() {
        this->predicatesManager.insertBack(std::make_shared<predicates::Call>(*this));
        this->predicatesManager.insertBack(std::make_shared<predicates::Unify>(*this));
        this->predicatesManager.insertBack(std::make_shared<predicates::And>(*this));
        this->predicatesManager.insertBack(std::make_shared<predicates::Or>(*this));
        this->predicatesManager.insertBack(std::make_shared<predicates::Print>(*this));
        this->predicatesManager.insertBack(std::make_shared<predicates::Module>(*this));
        this->predicatesManager.insertBack(std::make_shared<predicates::False>(*this));
        this->predicatesManager.insertBack(std::make_shared<predicates::True>(*this));
    }

    void Interpreter::execute(const ast::Term::Pointer& term) {
        auto instance = predicates::Call(*this).createCaller(term);
        instance->next();
    }

    PredicatesManager& Interpreter::getPredicatesManager() {
        return this->predicatesManager;
    }

    std::stack<Predicate::Instance>& Interpreter::getInstances() {
        return this->instances;
    }
};
