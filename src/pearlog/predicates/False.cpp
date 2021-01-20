#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/False.hpp>
#include <iostream>

namespace pear::pearlog::predicates {
    bool False::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
            term->getLexeme().getContent() == "false" &&
            term->getChildren().empty();
    }

    bool False::execute(Interpreter& interpreter, const ast::Term::Pointer& term) const {
        return false;
    }
}
