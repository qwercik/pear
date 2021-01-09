#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/PredicatesManager.hpp>
#include <iostream>

namespace pear::pearlog {
    void PredicatesManager::insertFront(Predicate::Pointer&& predicate) {
        this->insert(this->predicates.begin(), std::move(predicate));
    }

    void PredicatesManager::insertBack(Predicate::Pointer&& predicate) {
        this->insert(this->predicates.end(), std::move(predicate));
    }

    bool PredicatesManager::executeNext(Iterator& iterator, Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutionsList) const {
        for (; iterator != this->predicates.end(); iterator++) {
            auto& predicate = *iterator;

            if (predicate->execute(interpreter, term, substitutionsList)) {
                iterator++;
                return true;
            }
        }

        return false;
    }

    PredicatesManager::Iterator PredicatesManager::getStart() {
        return this->predicates.begin();
    }

    PredicatesManager::Iterator PredicatesManager::getEnd() {
        return this->predicates.end();
    }

    bool PredicatesManager::isEnd(const Iterator& iterator) {
        return iterator == this->predicates.end();
    }

    void PredicatesManager::insert(Iterator iterator, Predicate::Pointer&& predicate) {
        this->predicates.insert(iterator, std::move(predicate));
    }
}
