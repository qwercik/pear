#pragma once

#include <iostream>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    class TermPrinter {
    public:
        TermPrinter(const Term::Pointer& term);
        friend std::ostream& operator<<(std::ostream& stream, const TermPrinter& term);

    protected:
        static void print(std::ostream& stream, const Term::Pointer& term);

    private:
        const Term::Pointer& term;
    };
}

