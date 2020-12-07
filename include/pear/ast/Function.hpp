#pragma once

#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    class Function : public Term {
    public:
        Function(const lexer::Lexeme& lexeme);

        std::string getName() const;
        auto getArguments() const;
        std::size_t getArity() const;
    };
}
