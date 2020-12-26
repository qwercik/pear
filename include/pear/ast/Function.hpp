#pragma once

#include <pear/ast/Term.hpp>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Function : public Term {
    public:
        Function(const lexer::Lexeme& lexeme) :
            Term(Term::Type::FUNCTION, lexeme)
        {   
        }
    };
}
