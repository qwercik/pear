#pragma once

#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::ast {
    class Variable : public Term {
    public:
        Variable(const lexer::Lexeme& lexeme);

        std::string getName() const;
        
        virtual void accept(TermVisitor *visitor) override;
        virtual Pointer clone() const override;

        bool operator==(const Variable& variable) const;
        bool operator!=(const Variable& variable) const;
    };
}
