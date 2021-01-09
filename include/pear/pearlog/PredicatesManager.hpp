#pragma once

#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>

namespace pear::pearlog {
    class Interpreter;

    class PredicatesManager {
    public:
        using Container = std::list<Predicate::Pointer>;
        using Iterator = Container::const_iterator;

        void insertFront(Predicate::Pointer&& predicate);
        void insertBack(Predicate::Pointer&& predicate);

        Iterator getStart();
        Iterator getEnd();
        bool isEnd(const Iterator& iterator);

        bool executeNext(Iterator& iterator, Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutionsList) const;

    private:
        void insert(Iterator iterator, Predicate::Pointer&& predicate);

        Container predicates;
    };
}
