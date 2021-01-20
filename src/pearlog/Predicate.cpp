#include <pear/pearlog/Predicate.hpp>

namespace pear::pearlog {
    Predicate::Predicate(Interpreter& interpreter) :
            interpreter(interpreter)
    {
    }

    const std::list<Substitution>& Predicate::Instance::getSubstitutions() const {
        return this->substitutions;
    }

    std::list<Substitution>& Predicate::Instance::getSubstitutions() {
        return this->substitutions;
    }

    std::unique_ptr<Predicate::Instance> Predicate::createInstance(const ast::Term::Pointer& term) const {
        return this->createInstanceBackend(term);
    }
}
