#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/True.hpp>

namespace pear::pearlog::predicates {
    bool True::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION
            && term->getChildren().empty()
            && term->getLexeme().getContent() == "true";
    }

    bool True::execute(const ast::Term::Pointer& term) const {
        return true;
    }
}
