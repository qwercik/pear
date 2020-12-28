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

        auto& children = term->getChildren();
        if (children.size() != 2) {
            throw InterpreterException(
                "module should have 2 params"
            );
        }

        auto firstIt = children.begin();
        auto secondIt = std::next(firstIt);

        auto& first = *firstIt;
        auto& second = *secondIt;

        std::cout << "Unifikuję termy: " << ast::TermPrinter(first) << " oraz " << ast::TermPrinter(second) << "\n\n";


        try {
            Unification unification(first, second);
            auto& res = unification.getResult();

            std::cout << "Udało się wykonać unifikację\n";

            for (const auto& subst : res.getSubstitutions()) {
                auto& dst = subst.getDestination();
                auto& src = subst.getSource();

                std::cout << ast::TermPrinter(dst) << " = " << ast::TermPrinter(src) << '\n';
            }

            std::cout << '\n';
            std::cout << "Term po podstawieniu: " << ast::TermPrinter(res.getTerm()) << '\n';
        } catch (const UnificationException& exception) {
            std::cout << "Nie udało się wykonać unifikacji\n";
        } catch (...) {
            std::cout << "Wystąpił jakiś błąd\n";
        }
    }
};

