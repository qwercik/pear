#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Call.hpp>

namespace pear::pearlog::predicates {
    bool Call::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION && term->getLexeme().getContent() == "call" && term->getChildren().size() == 1;
    }

    bool Call::execute(Interpreter& interpreter, const ast::Term::Pointer& term) const {
        auto& executable = term->getChildren().front();
        return interpreter.executeNext(term);
    }
}
