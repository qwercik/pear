#pragma once

#include <pear/ast/Term.hpp>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Variable : public Term {
    public:
        Variable(const lexer::Lexeme& lexeme) :
            Term(Term::Type::VARIABLE, lexeme)
        {   
        }
    };
}
