#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/False.hpp>

namespace pear::pearlog::predicates {
    False::False(Interpreter& interpreter) :
            BuiltinPredicate(interpreter)
    {
    }

    bool False::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
               term->getLexeme().getContent() == "true" &&
               term->getChildren().empty();
    }

    std::unique_ptr<Predicate::Instance> False::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<False::Instance>();
    }

    bool False::Instance::next() {
        return false;
    }
}
