#pragma once

#include <pear/ast/Term.hpp>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Literal : public Term {
    public:
        Literal(const lexer::Lexeme& lexeme) :
            Term(Term::Type::LITERAL, lexeme)
        {   
        }
    };
}
