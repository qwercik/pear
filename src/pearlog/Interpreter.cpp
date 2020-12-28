#include <iostream>
#include <pear/pearlog/Interpreter.hpp>
#include <pear/pearlog/InterpreterException.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>

#include <pear/pearlog/Unification.hpp>
#include <pear/pearlog/UnificationException.hpp>

namespace pear::pearlog {
    void Interpreter::execute(const ast::Term::Pointer& term) {
        if (term->getType() != ast::Term::Type::FUNCTION || term->getLexeme().getContent() != "module") {
            throw InterpreterException(
                "Each program file should be nested in global module() function"
            );
        }

        for (const auto& moduleEntry : term->getChildren()) {
            std::cout << moduleEntry->getLexeme().getContent() << '\n';
        }
    }
};

