#pragma once

#include <memory>
#include <functional>
#include <pear/ast/Term.hpp>

namespace pear::pearlog {
    class Interpreter;

    class Predicate {
    public:
        using Pointer = std::shared_ptr<Predicate>;

        virtual bool unify(const ast::Term::Pointer& term) const = 0;

        virtual void in(Interpreter& interpreter, const ast::Term::Pointer& term) = 0;
        virtual bool next() = 0;
        virtual void out() = 0;
    };
}
