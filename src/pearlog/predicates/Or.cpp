#include <pear/ast/Term.hpp>
#include <pear/ast/Function.hpp>
#include <pear/pearlog/predicates/Or.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <iostream>

namespace pear::pearlog::predicates {
    Or::Or(Interpreter& interpreter) :
            BuiltinPredicate(interpreter)
    {
    }

    bool Or::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
               term->getLexeme().getContent() == "or";
    }

    std::unique_ptr<Predicate::Instance> Or::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<Or::Instance>(this->interpreter, term);
    }

    Or::Instance::Instance(Interpreter& interpreter, const ast::Term::Pointer& term) :
        interpreter(interpreter),
        term(term->clone()),
        childIterator(term->getChildren().cbegin()),
        endIterator(term->getChildren().cend())
    {
    }

    bool Or::Instance::next() {
        for (; this->childIterator != endIterator; this->childIterator++) {
            if (!this->childInstance) {
                this->childInstance = predicates::Call(this->interpreter).createCaller(*this->childIterator);
            }

            if (this->childInstance->next()) {
                return true;
            }

            this->childInstance.reset(nullptr);
        }

        return false;
    }
}
