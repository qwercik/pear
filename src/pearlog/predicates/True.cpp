#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/True.hpp>
#include <iostream>

namespace pear::pearlog::predicates {
    bool True::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
            term->getLexeme().getContent() == "true" &&
            term->getChildren().empty();
    }
}
