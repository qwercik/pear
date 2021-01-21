#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/predicates/And.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <iostream>
#include <pear/ast/TermPrinter.hpp>

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
        term(term->clone()),
        currentChild(term->getChildren().cbegin()),
        lastChild(std::next(term->getChildren().cend(), -1))
    {
        this->childInstances.push(nullptr);
    }

    bool And::Instance::next() {
        while (!this->childInstances.empty()) {
            auto& currentInstance = this->childInstances.top();

            if (!currentInstance) {
                auto callTerm = (*this->currentChild)->clone();
                for (const auto& substitution : this->substitutions) {
                    substitution.apply(callTerm);
                }

                currentInstance = predicates::Call(this->interpreter).createCaller(callTerm);
            }

            if (currentInstance->next()) {
                this->substitutions.insert(this->substitutions.end(), currentInstance->getSubstitutions().begin(), currentInstance->getSubstitutions().end());

                if (this->currentChild == this->lastChild) {
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
