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
                std::cout << "query " << ast::TermPrinter(executable) << ":\n";

                auto iterator = interpreter.getPredicatesManager().getStart();
                while (true) {
                    bool result = interpreter.execute(iterator, executable, substitutions);
                    std::cout << "result: " << result << "\n";

                    if (result) {
                        break;
                    }
                }
            }
        }

        return true;
    }
}
