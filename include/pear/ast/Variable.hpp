#pragma once

#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    class Variable : public Term {
    public:
        Variable(const lexer::Lexeme& lexeme);

        std::string getName() const;
    };
}
