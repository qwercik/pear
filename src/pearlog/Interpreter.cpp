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

namespace pear::pearlog {
    Interpreter::Interpreter() {
        this->predicatesManager.insertBack(std::make_shared<predicates::And>());
        this->predicatesManager.insertBack(std::make_shared<predicates::Or>());
        this->predicatesManager.insertBack(std::make_shared<predicates::Call>());
        this->predicatesManager.insertBack(std::make_shared<predicates::Eval>());
        this->predicatesManager.insertBack(std::make_shared<predicates::Print>());
        this->predicatesManager.insertBack(std::make_shared<predicates::Module>());
        this->predicatesManager.insertBack(std::make_shared<predicates::False>());
        this->predicatesManager.insertBack(std::make_shared<predicates::True>());
    }

    void Interpreter::execute(const ast::Term::Pointer& term) {
        this->iterators = std::stack<PredicatesManager::ConstIterator>();
        this->substitutions = std::stack<std::list<Substitution>>();

        this->iterators.push(this->getPredicatesManager().getContainer().begin());
        this->substitutions.push(std::list<Substitution>());

        this->call(term);
        while (this->next()) {
            // Do nothing
        }
        this->back();
    }

    void Interpreter::call(const ast::Term::Pointer& term) {
        auto termCopy = term->clone();
        for (const auto& substitution : this->getSubstitutions().top()) {
            substitution.apply(termCopy);
        }

        this->terms.push(termCopy);
        this->iterators.push(this->predicatesManager.getContainer().end());
        this->substitutions.push(std::list<Substitution>());
    }

    bool Interpreter::next() {
        auto& iterator = this->iterators.top();
        const auto& end = this->predicatesManager.getContainer().end();

        for (; iterator != end; iterator++) {
            const auto& predicate = *iterator;
            const auto& term = this->terms.top();
            if (predicate->unify(term) && predicate->next(*this, term)) {
                iterator++;
                return true;
            }
        }

        return false;
    }

    void Interpreter::back() {
        this->terms.pop();
        this->iterators.pop();
        this->substitutions.pop();
    }

    void Interpreter::updateScopeId(int diff) {
        this->currentScopeId += diff;
    }

    PredicatesManager &Interpreter::getPredicatesManager() {
        return this->predicatesManager;
    }

    std::stack<std::list<Substitution>> &Interpreter::getSubstitutions() {
        return this->substitutions;
    }

    std::stack<PredicatesManager::ConstIterator>& Interpreter::getIterators() {
        return this->iterators;
    }

    int Interpreter::getScopeId() const {
        return this->currentScopeId;
    }
};
