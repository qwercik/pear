#pragma once

#include <string>

namespace pear::ast {
    class Term;
    class Literal;
    class Variable;
    class Function;

    class TermVisitor {
    public:
        virtual void visitLiteral(Literal *literal) = 0;
        virtual void visitVariable(Variable *variable) = 0;
        virtual void visitFunction(Function *function) = 0;
    };
}

