#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/Print.hpp>

namespace pear::pearlog::predicates {
    bool Print::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION
            && term->getLexeme().getContent() == "print";
    }

    bool Print::execute(const ast::Term::Pointer& term) const {
        for (const auto& argument : term->getChildren()) {
            std::cout << argument->getLexeme().getContent() << '\n';
        }

        return true;
    }
}
