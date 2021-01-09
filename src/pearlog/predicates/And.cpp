#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/And.hpp>
#include <iostream>

namespace pear::pearlog::predicates {
    bool And::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        if (term->getType() != ast::Term::Type::FUNCTION ||
            term->getLexeme().getContent() != "and") {
            return false;
        }

        for (auto& child : term->getChildren()) {
            if (!interpreter.execute(child, substitutions)) {
                return false;
            }
        }

        return true;
    }
}
