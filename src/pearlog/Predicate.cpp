#include <pear/pearlog/Predicate.hpp>

namespace pear::pearlog {
    Predicate::Predicate(Interpreter& interpreter) :
            interpreter(interpreter)
    {
    }

    const std::list<Substitution>& Predicate::Instance::getSubstitutions() const {
        return this->substitutions;
    }

    std::unique_ptr<Instance> Predicate::createInstance(const ast::Term::Pointer& term) const {
        this->createInstanceBackend(term);
    }
}
