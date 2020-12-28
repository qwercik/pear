#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/False.hpp>

namespace pear::pearlog::predicates {
    bool False::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION
            && term->getChildren().empty()
            && term->getLexeme().getContent() == "false";
    }

    bool False::execute(const ast::Term::Pointer& term) const {
        return false;
    }
}
