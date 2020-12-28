#pragma once

#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>

namespace pear::pearlog {
    class PredicatesManager {
    public:
        using Container = std::list<Predicate::Pointer>;
        using Iterator = Container::iterator;

        void insertFront(Predicate::Pointer&& predicate);
        void insertBack(Predicate::Pointer&& predicate);

        void forEachMatching(const ast::Term::Pointer& term, std::function<void(const Predicate::Pointer& predicate)> callback) const;

    private:
        void insert(Iterator iterator, Predicate::Pointer&& predicate);

        Container predicates;
    };
}
