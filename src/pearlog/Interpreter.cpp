#include <iostream>
#include <pear/pearlog/Interpreter.hpp>
#include <pear/pearlog/InterpreterException.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>

#include <pear/pearlog/Unification.hpp>

namespace pear::pearlog {
    void Interpreter::execute(ast::Term::Pointer node) {
        if (!node->isFunction() || node->getLexeme().getContent() != "module") {
            throw InterpreterException(
                "Each program file should be nested in global module() function"
            );
        }

        auto children = node->getChildren();
        if (children.size() != 2) {
            throw InterpreterException(
                "module should have 2 params"
            );
        }

        auto firstIt = children.begin();
        auto secondIt = std::next(firstIt);

        auto first = (*firstIt).get();
        auto second = (*secondIt).get();

        std::cout << "Unifikuję termy: " << ast::TermPrinter(first) << " " << ast::TermPrinter(second) << "\n\n";


        Unification unif(first, second);
        auto res = unif.getResult();
       
        if (res.error) {
            std::cout << "Nie udało się wykonać unifikacji\n";
        } else {
            std::cout << "Udało się wykonać unifikację\n";
        }
 
        for (const auto& subst : res.substitutions) {
            auto dst = subst.getDestination();
            auto src = subst.getSource();

            std::cout << ast::TermPrinter(dst) << " = " << ast::TermPrinter(src) << '\n';
        }
    }
};

