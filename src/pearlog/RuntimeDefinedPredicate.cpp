#include <pear/pearlog/RuntimeDefinedPredicate.hpp>
#include <pear/pearlog/SideUnification.hpp>
#include <pear/pearlog/UnificationException.hpp>
#include <pear/pearlog/Interpreter.hpp>
#include <pear/pearlog/Unification.hpp>

namespace pear::pearlog {
    RuntimeDefinedPredicate::RuntimeDefinedPredicate(const ast::Term& definition) {
        const auto& iterator = definition.getChildren().begin();
        this->header = (*iterator)->clone();
        this->body = (*std::next(iterator))->clone();
    }

    bool RuntimeDefinedPredicate::unify(const ast::Term::Pointer& pointer) const {
        try {
            Unification unification(this->header, pointer);
            return true;
        } catch (const UnificationException& e) {
            return false;
        }
    }

    bool RuntimeDefinedPredicate::execute(Interpreter& interpreter, const ast::Term::Pointer& term) const {
        try {
            int scopeId = interpreter.getScopeId();

            auto termCopy = term->clone();
            toggleVariablesScopeId(termCopy, scopeId);

            interpreter.getSubstitutions().push(SideUnification(this->header, termCopy).getResult().getSubstitutions());
            interpreter.getIterators().push(interpreter.getPredicatesManager().getContainer().begin());

            auto result = interpreter.executeNext(termCopy);

            auto headerCopy = this->header->clone();
            for (const auto& substitution : interpreter.getSubstitutions().top()) {
                substitution.apply(headerCopy);
            }

            interpreter.getSubstitutions().pop();
            interpreter.getIterators().pop();

            auto resultSubstitutions = SideUnification(termCopy, headerCopy).getResult().getSubstitutions();
            for (auto& substitution : resultSubstitutions) {
                toggleVariablesScopeId(substitution.getDestination(), scopeId);
                toggleVariablesScopeId(substitution.getSource(), scopeId);
            }

            auto& scope = interpreter.getSubstitutions().top();
            scope.insert(scope.begin(), resultSubstitutions.begin(), resultSubstitutions.end());

            return result;
        } catch (const UnificationException& e) {
            return false;
        }
    }

    void RuntimeDefinedPredicate::toggleVariablesScopeId(ast::Term::Pointer& pointer, int currentScopeId) const {
        if (pointer->getType() == ast::Term::Type::VARIABLE) {
            if (pointer->getScopeId() == -1) {
                pointer->setScopeId(currentScopeId);
            } else {
                pointer->setScopeId(-1);
            }
        } else if (pointer->getType() == ast::Term::Type::FUNCTION) {
            for (auto& child : pointer->getChildren()) {
                this->toggleVariablesScopeId(child, currentScopeId);
            }
        }
    }
}