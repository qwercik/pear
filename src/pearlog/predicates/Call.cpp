#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/predicates/Call.hpp>

namespace pear::pearlog::predicates {
    Call::Call(Interpreter& interpreter) :
        BuiltinPredicate(interpreter)
    {
    }

    bool Call::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION && term->getLexeme().getContent() == "call" && term->getChildren().size() == 1;
    }

    std::unique_ptr<Predicate::Instance> Call::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<Call::Instance>(this->interpreter, term);
    }

    Call::Instance::Instance(Interpreter& interpreter, const ast::Term::Pointer& term) :
        interpreter(interpreter),
        child(term),
        iterator(interpreter.getPredicatesManager().getContainer().begin()),
        predicateInitialized(false)
    {
    }

    bool Call::Instance::next() {
        auto end = this->interpreter.getPredicatesManager().getContainer().end();
        for (; this->iterator != end; this->iterator++) {
            if (!this->predicateInitialized) {
            }
        }
    }
}
