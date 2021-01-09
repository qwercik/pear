#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/True.hpp>

namespace pear::pearlog::predicates {
    bool True::execute(const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        return true;
    }
}
