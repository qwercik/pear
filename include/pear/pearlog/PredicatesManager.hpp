#pragma once

#include <list>
#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>

namespace pear::pearlog {
    class PredicatesManager {
    public:
        using Container = std::list<Predicate::Pointer>;
        using Iterator = Container::iterator;
        using ConstIterator = Container::const_iterator;

        void insertFront(Predicate::Pointer&& predicate);
        void insertBack(Predicate::Pointer&& predicate);
        const Container& getContainer();

    private:
        void insert(Iterator iterator, Predicate::Pointer&& predicate);

        Container predicates;
    };
}
