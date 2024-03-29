#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Module.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <iostream>
#include <pear/ast/TermPrinter.hpp>

namespace pear::pearlog::predicates {
    Module::Module(Interpreter& interpreter) :
            BuiltinPredicate(interpreter)
    {
    }

    bool Module::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
               term->getLexeme().getContent() == "module";
    }

    std::unique_ptr<Predicate::Instance> Module::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<Module::Instance>(this->interpreter, term);
    }

    Module::Instance::Instance(Interpreter& interpreter, const ast::Term::Pointer& term) :
            interpreter(interpreter),
            term(term->clone()),
            alreadyCalled(false)
    {
    }

    bool Module::Instance::isQuery(const ast::Term::Pointer& term) {
        return term->getType() == ast::Term::Type::FUNCTION &&
               term->getLexeme().getContent() == "query" &&
               term->getChildren().size() == 1;
    }

    bool Module::Instance::next() {
        if (this->alreadyCalled) {
            return false;
        }

        for (const auto& moduleEntry : term->getChildren()) {
            if (this->isQuery(moduleEntry)) {
                const auto& queryTerm = moduleEntry->getChildren().front();
                auto instance = predicates::Call(this->interpreter).createCaller(queryTerm);
                while (instance->next()) {
                }
            }
        }

        this->alreadyCalled = true;
        return true;
    }
}

