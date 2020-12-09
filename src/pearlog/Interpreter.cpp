#include <iostream>
#include <pear/pearlog/Interpreter.hpp>
#include <pear/pearlog/InterpreterException.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>

namespace pear::pearlog {
    void Interpreter::execute(ast::Term::Pointer node) {
        if (!node->isFunction() || node->getLexeme().getContent() != "module") {
            throw InterpreterException(
                "Each program file should be nested in global module() function"
            );
        }

        for (const auto& child : node->getChildren()) {
            if (child->isFunction() && child->getLexeme().getContent() == "def") {
                auto header = child->getChildren().front().get();
                std::cout << "Definicja predykatu " << pear::ast::TermPrinter(header) << '\n';
            }
        }
    }
};

