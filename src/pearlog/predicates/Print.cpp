#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/Print.hpp>

namespace pear::pearlog::predicates {
    bool Print::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        if (term->getType() != ast::Term::Type::FUNCTION || term->getLexeme().getContent() != "print") {
            return false;
        }

        for (const auto& argument : term->getChildren()) {
            std::cout << ast::TermPrinter(argument) << '\n';
        }

        return true;
    }
}
