#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/False.hpp>

namespace pear::pearlog::predicates {
    bool False::execute(const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        return false;
    }
}
