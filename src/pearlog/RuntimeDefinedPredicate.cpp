#include <pear/pearlog/RuntimeDefinedPredicate.hpp>
#include <pear/pearlog/SideUnification.hpp>
#include <pear/pearlog/UnificationException.hpp>
#include <pear/pearlog/Interpreter.hpp>
#include <pear/pearlog/Unification.hpp>
#include <pear/pearlog/predicates/Call.hpp>

namespace pear::pearlog {
    RuntimeDefinedPredicate::Instance::Instance(Interpreter& interpreter, const ast::Term::Pointer& header, const ast::Term::Pointer& body, const ast::Term::Pointer& term) :
        interpreter(interpreter),
        header(header),
        body(body),
        term(term->clone()),
        scopeId( interpreter.getInstances().size())
    {
        toggleVariablesScopeId(this->term, scopeId);

        auto substitutions = SideUnification(this->header, this->term).getResult().getSubstitutions();
        this->caller = predicates::Call(interpreter).createCaller(this->term);
        this->caller->getSubstitutions().insert(caller->getSubstitutions().begin(), substitutions.begin(), substitutions.end());
    }

    bool RuntimeDefinedPredicate::Instance::next() {
        try {
            auto result = this->caller->next();
            auto headerCopy = this->header->clone();
            for (const auto& substitution : this->caller->getSubstitutions()) {
                substitution.apply(headerCopy);
            }

            auto resultSubstitutions = SideUnification(this->term, headerCopy).getResult().getSubstitutions();
            for (auto& substitution : resultSubstitutions) {
                toggleVariablesScopeId(substitution.getDestination(), scopeId);
                toggleVariablesScopeId(substitution.getSource(), scopeId);
            }

            this->substitutions.insert(this->substitutions.begin(), resultSubstitutions.begin(), resultSubstitutions.end());

            return result;
        } catch (const UnificationException& e) {
            return false;
        }
    }

    void RuntimeDefinedPredicate::Instance::toggleVariablesScopeId(ast::Term::Pointer& pointer, int currentScopeId) const {
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

    std::unique_ptr<Predicate::Instance> RuntimeDefinedPredicate::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<RuntimeDefinedPredicate::Instance>(this->interpreter, header, body, term);
    }

    bool RuntimeDefinedPredicate::unify(const ast::Term::Pointer& term) const {
        try {
            Unification unification(this->header, term);
            return true;
        } catch (const UnificationException& e) {
            return false;
        }
    }

    RuntimeDefinedPredicate::RuntimeDefinedPredicate(Interpreter& interpreter, const ast::Term::Pointer &definition) :
        Predicate(interpreter),
        header(*definition->getChildren().begin()),
        body(*std::next(definition->getChildren().begin()))
    {
    }
}