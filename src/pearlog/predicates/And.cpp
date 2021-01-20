#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/predicates/And.hpp>

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
        interpreter(interpreter)
    {
        this->childrenNumber = term->getChildren().size();

        this->iterators.push(interpreter.getPredicatesManager().getContainer().begin());
        this->substitutions.push(interpreter.getSubstitutions().top());
        this->predicateInitialized.push(false);

        auto termCopy = term->clone();
        for (const auto& substitution : this->substitutions.top()) {
            substitution.apply(termCopy);
        }
        this->terms.push(termCopy);
    }

    bool And::Instance::next() {
        // TODO: nie trzeba będzie tu czasami inkrementować iteratora?!
        auto end = this->interpreter.getPredicatesManager().getContainer().end();

        while (!this->iterators.empty()) {
            auto& iterator = this->iterators.top();
            auto& term = this->terms.top();

            for (; iterator != end; iterator++) {
                const auto& predicate = *iterator;

                if (!this->predicateInitialized.top()) {
                    if (!predicate->unify(term)) {
                        continue;
                    }

                    predicate->in(*this->interpreter, term);
                    this->predicateInitialized.top() = true;
                }

                if (predicate->next()) {
                    if (this->iterators.size() < this->childrenNumber) {
                        this->iterators.push(this->interpreter.getPredicatesManager().getContainer().begin());
                        this->substitutions.push(this->substitutions.top());
                        this->predicateInitialized.push(false);

                        auto termCopy = term->clone();
                        for (const auto& substitution : this->substitutions.top()) {
                            substitution.apply(termCopy);
                        }
                        this->terms.push(termCopy);
                    }

                    return true;
                }
            }

            this->iterators.pop();
            this->substitutions.pop();
            this->terms.pop();
            this->predicateInitialized.pop();

            this->iterators.top()++;
            this->predicateInitialized.top() = false;
        }

        return false;
    }
}
