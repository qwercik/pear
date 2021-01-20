#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/True.hpp>

namespace pear::pearlog::predicates {
    True::True(Interpreter& interpreter) :
        BuiltinPredicate(interpreter)
    {
    }

    bool True::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION &&
               term->getLexeme().getContent() == "true" &&
               term->getChildren().empty();
    }

    std::unique_ptr<Predicate::Instance> True::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<True::Instance>();
    }

    bool True::Instance::next() {
        if (this->alreadyCalled) {
            return false;
        }

        this->alreadyCalled = true;
        return true;
    }
}
