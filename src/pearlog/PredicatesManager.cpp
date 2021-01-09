#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/PredicatesManager.hpp>

namespace pear::pearlog {
    void PredicatesManager::insertFront(Predicate::Pointer&& predicate) {
        this->insert(this->predicates.begin(), std::move(predicate));
    }

    void PredicatesManager::insertBack(Predicate::Pointer&& predicate) {
        this->insert(this->predicates.end(), std::move(predicate));
    }

    void PredicatesManager::forEachMatching(const ast::Term::Pointer& term, std::function<void(const Predicate::Pointer& predicate)> callback) const {
        for (const auto& predicate : this->predicates) {
            /*if (predicate->unify(term)) {
                callback(predicate);
            }*/
        }
    }

    void PredicatesManager::insert(Iterator iterator, Predicate::Pointer&& predicate) {
        this->predicates.insert(iterator, std::move(predicate));
    }
}
