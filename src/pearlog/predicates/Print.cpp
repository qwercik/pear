#include <iostream>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/predicates/Print.hpp>

namespace pear::pearlog::predicates {
    Print::Print(Interpreter& interpreter) :
            BuiltinPredicate(interpreter)
    {
    }

    bool Print::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION && term->getLexeme().getContent() == "print";
    }

    std::unique_ptr<Predicate::Instance> Print::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<Print::Instance>(term);
    }

    Print::Instance::Instance(const ast::Term::Pointer& term) :
        term(term->clone())
    {
    }

    bool Print::Instance::next() {
        if (this->alreadyCalled) {
            return false;
        }

        if (term->getChildren().empty()) {
            std::cout << '\n';
        }

        for (const auto& argument : term->getChildren()) {
            std::cout << ast::TermPrinter(argument) << ' ';
        }

        std::cout << '\n';

        this->alreadyCalled = true;
        return true;
    }
}
