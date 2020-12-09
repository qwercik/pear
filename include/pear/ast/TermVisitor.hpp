#pragma once

#include <string>

namespace pear::ast {
    class Term;
    class Literal;
    class Variable;
    class Function;

    class TermVisitor {
    public:
        virtual void visit(Literal *literal) = 0;
        virtual void visit(Variable *variable) = 0;
        virtual void visit(Function *function) = 0;
    };
}

