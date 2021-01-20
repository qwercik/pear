#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Module.hpp>

namespace pear::pearlog::predicates {
    bool Module::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
            term->getLexeme().getContent() == "module";
    }

    bool Module::execute(Interpreter& interpreter, const ast::Term::Pointer& term) const {
        for (const auto& moduleEntry : term->getChildren()) {
            if (this->isQuery(moduleEntry)) {
                const auto& queryTerm = moduleEntry->getChildren().front();
                interpreter.execute(queryTerm);
            }
        }

        return true;
    }

    bool Module::isQuery(const ast::Term::Pointer& term) {
        return term->getType() == ast::Term::Type::FUNCTION &&
        term->getLexeme().getContent() == "query" &&
        term->getChildren().size() == 1;
    }
}
