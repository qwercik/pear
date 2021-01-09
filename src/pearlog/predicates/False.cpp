#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/False.hpp>
#include <iostream>

namespace pear::pearlog::predicates {
    bool False::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        return false;
    }
}
