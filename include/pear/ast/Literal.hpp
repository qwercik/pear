#pragma once

#include <string>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::ast {
    class Literal : public Term {
    public:
        Literal(const lexer::Lexeme& lexeme) :
            Term(lexeme)
        {
        }

        std::string getContent() const {
            return this->getLexeme().getContent();
        }

        virtual void accept(TermVisitor *visitor) override {
            visitor->visit(this);
        }

        bool operator==(const Literal& literal) const {
            return this->getContent() == literal.getContent();
        }
        
        bool operator!=(const Literal& literal) const {
            return !(*this == literal);
        }
    };
}

