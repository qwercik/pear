#pragma once

#include <string>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::ast {
    class Literal : public Term {
    public:
        Literal(const lexer::Lexeme& lexeme);

        std::string getContent() const;

        virtual void accept(TermVisitor *visitor) override;
        virtual Pointer clone() const override;

        bool operator==(const Literal& literal) const;
        bool operator!=(const Literal& literal) const;
    };
}

