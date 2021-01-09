#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Call.hpp>

namespace pear::pearlog::predicates {
    bool Call::execute(Interpreter& interpreter, const ast::Term::Pointer& term, std::list<Substitution>& substitutions) const {
        if (term->getType() != ast::Term::Type::FUNCTION ||
            term->getLexeme().getContent() != "call" ||
            term->getChildren().size() != 1) {
            return false;
        }

        auto& executable = term->getChildren().front();
        auto iterator = interpreter.getPredicatesManager().getStart();
        return interpreter.execute(iterator, executable, substitutions);
    }
}
