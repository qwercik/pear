#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/Module.hpp>

namespace pear::pearlog::predicates {
    bool Module::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        if (term->getType() != ast::Term::Type::FUNCTION || term->getLexeme().getContent() != "module") {
            return false;
        }

        for (const auto& moduleEntry : term->getChildren()) {
            if (moduleEntry->getType() == ast::Term::Type::FUNCTION &&
                moduleEntry->getLexeme().getContent() == "query" &&
                moduleEntry->getChildren().size() == 1) {
                auto& executable = moduleEntry->getChildren().front();
                std::cout << ast::TermPrinter(executable) << ": " << interpreter.execute(executable, substitutions) << "\n";
            }
        }

        return true;
    }
}
