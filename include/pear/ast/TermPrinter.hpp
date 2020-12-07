#pragma once

#include <iostream>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    class TermPrinter {
    public:
        TermPrinter(const Term& node);
        friend std::ostream& operator<<(std::ostream& stream, const TermPrinter& node);

    protected:
        static void print(std::ostream& stream, const Term *node);

    private:
        Term node;
    };
}

