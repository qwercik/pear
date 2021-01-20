#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/predicates/And.hpp>
#include <pear/pearlog/predicates/Call.hpp>

namespace pear::pearlog::predicates {
    And::And(Interpreter& interpreter) :
        BuiltinPredicate(interpreter)
    {
    }

    bool And::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION && term->getLexeme().getContent() == "and";
    }

    std::unique_ptr<Predicate::Instance> And::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<And::Instance>(this->interpreter, term);
    }

    And::Instance::Instance(Interpreter& interpreter, const ast::Term::Pointer& term) :
        interpreter(interpreter),
        term(term),
        currentChild(term->getChildren().cbegin())
    {
    }

    bool And::Instance::next() {
        this->childInstances.push(nullptr);

        while (!this->childInstances.empty()) {
            auto& currentInstance = this->childInstances.top();

            if (!currentInstance) {
                currentInstance = predicates::Call(this->interpreter).createCaller(*this->currentChild);
            }

            if (currentInstance->next()) {
                if (this->currentChild == this->term->getChildren().cend()) {
                    return true;
                } else {
                    this->currentChild++;
                    this->childInstances.push(nullptr);
                }
            } else {
                this->currentChild--;
                this->childInstances.pop();
            }
        }

        return false;
    }
}
