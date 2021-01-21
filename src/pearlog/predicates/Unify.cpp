#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/predicates/Unify.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <pear/ast/Function.hpp>
#include <iostream>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/Unification.hpp>

namespace pear::pearlog::predicates {
    Unify::Unify(Interpreter& interpreter) :
        BuiltinPredicate(interpreter)
    {
    }

    bool Unify::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION && term->getLexeme().getContent() == "unify" && term->getChildren().size() == 2;
    }

    std::unique_ptr<Predicate::Instance> Unify::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<Unify::Instance>(this->interpreter, term);
    }

    Unify::Instance::Instance(Interpreter& interpreter, const ast::Term::Pointer& term) :
        interpreter(interpreter),
        first(term->getChildren().front()->clone()),
        second((*std::next(term->getChildren().begin()))->clone())
    {
    }

    bool Unify::Instance::next() {
        if (alreadyCalled) {
            return false;
        }

        auto result = Unification(this->first, this->second).getResult().getSubstitutions();
        this->substitutions.insert(this->substitutions.begin(), result.begin(), result.end());

        alreadyCalled = true;
        return true;
    }
}
