#include <pear/ast/Term.hpp>
#include <pear/pearlog/Predicate.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <pear/ast/Function.hpp>
#include <iostream>
#include <pear/ast/TermPrinter.hpp>

namespace pear::pearlog::predicates {
    Call::Call(Interpreter& interpreter) :
        BuiltinPredicate(interpreter)
    {
    }

    bool Call::unify(const ast::Term::Pointer& term) const {
        return term->getType() == ast::Term::Type::FUNCTION && term->getLexeme().getContent() == "call" && term->getChildren().size() == 1;
    }

    std::unique_ptr<Predicate::Instance> Call::createInstanceBackend(const ast::Term::Pointer& term) const {
        return std::make_unique<Call::Instance>(this->interpreter, term);
    }

    Call::Instance::Instance(Interpreter& interpreter, const ast::Term::Pointer& term) :
        interpreter(interpreter),
        child(term->getChildren().front()->clone()),
        iterator(interpreter.getPredicatesManager().getContainer().begin())
    {
    }

    bool Call::Instance::next() {
        auto end = this->interpreter.getPredicatesManager().getContainer().end();
        for (; this->iterator != end; this->iterator++) {
            const auto& predicate = *this->iterator;
            if (!this->childInstance) {
                if (!predicate->unify(child)) {
                    continue;
                }

                this->childInstance = predicate->createInstance(child);
            }

            if (this->childInstance->next()) {
                this->iterator++;
                return true;
            }

            this->childInstance.reset(nullptr);
        }

        return false;
    }

    std::unique_ptr<Predicate::Instance> Call::createCaller(const ast::Term::Pointer& term) const {
        auto function = std::make_unique<ast::Function>(lexer::Lexeme(lexer::Token::Type::IDENTIFIER, "call"));
        function->getChildren().push_back(term->clone());
        return this->createInstance(std::move(function));
    }
}
