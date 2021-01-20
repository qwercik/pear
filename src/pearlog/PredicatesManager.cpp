#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/PredicatesManager.hpp>
#include <iostream>

namespace pear::pearlog {
    void PredicatesManager::insertBack(Predicate::Pointer&& predicate) {
        this->insert(this->predicates.end(), std::move(predicate));
    }

    void PredicatesManager::insertFront(Predicate::Pointer&& predicate) {
        this->insert(this->predicates.begin(), std::move(predicate));
    }

    const PredicatesManager::Container& PredicatesManager::getContainer() {
        return this->predicates;
    }

    void PredicatesManager::insert(Iterator iterator, Predicate::Pointer&& predicate) {
        this->predicates.insert(iterator, std::move(predicate));
    }
}
