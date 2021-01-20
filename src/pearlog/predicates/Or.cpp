#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Or.hpp>

namespace pear::pearlog::predicates {
    bool Or::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
            term->getLexeme().getContent() == "or";
    }

    void Or::in(Interpreter& interpreter, const ast::Term::Pointer& term) {
        this->interpreter = &interpreter;

        this->currentChild = 0;
        this->childrenNumber = term->getChildren().size();
        this->term = term->clone();
        this->iterator = interpreter.getPredicatesManager().getContainer().begin();
        this->predicateInitialized = false;
    }

    bool Or::next() {
        while (this->currentChild < this->childrenNumber) {
            auto end = this->interpreter->getPredicatesManager().getContainer().end();
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
