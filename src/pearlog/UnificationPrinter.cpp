#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>
#include <pear/pearlog/UnificationPrinter.hpp>
#include <pear/pearlog/Unification.hpp>
#include <iostream>

namespace pear::pearlog {
    UnificationPrinter::UnificationPrinter(const Unification::Result& result) :
        result(result)
    {
    }

    std::ostream& operator<<(std::ostream& stream, const UnificationPrinter& printer) {
        for (const auto& substitution : printer.result.getSubstitutions()) {
            std::cout << ast::TermPrinter(substitution.getDestination()) << " = " << ast::TermPrinter(substitution.getSource()) << '\n';
        }

        return stream;
    }
}

