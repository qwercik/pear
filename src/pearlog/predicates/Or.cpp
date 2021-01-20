#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Or.hpp>

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
        term(term->clone())
    {
        this->currentChild = 0;
        this->childrenNumber = term->getChildren().size();
        this->iterator = interpreter.getPredicatesManager().getContainer().begin();
        this->predicateInitialized = false;
    }

    bool Or::Instance::next() {
        while (this->currentChild < this->childrenNumber) {
            auto end = this->interpreter.getPredicatesManager().getContainer().end();
            for (; this->iterator != end; this->iterator++) {
                auto& predicate = *this->iterator;

                if (!this->predicateInitialized) {
                    if (!predicate->unify(this->term)) {
                        continue;
                    }

                    predicate->in(*this->interpreter, this->term);
                    this->predicateInitialized = true;
                }

                if (predicate->next()) {
                    return true;
                }
            }
        }

        return false;
    }
}
