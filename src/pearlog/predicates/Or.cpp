#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Or.hpp>

namespace pear::pearlog::predicates {
    bool Or::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        if (term->getType() != ast::Term::Type::FUNCTION ||
            term->getLexeme().getContent() != "or") {
            return false;
        }

        auto result = false;
        for (auto& child : term->getChildren()) {
            std::list<Substitution> substitutionsCopy = substitutions;
            if (interpreter.execute(child, substitutionsCopy)) {
                result = true;
            }
        }

        return result;
    }
}
