#pragma once

#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::ast {
    class Function : public Term {
    public:
        Function(const lexer::Lexeme& lexeme);

        std::string getName() const;
        Term::List getArguments() const;
        std::size_t getArity() const;
        
        virtual void accept(TermVisitor *visitor) override;

        bool operator==(const Function& other) const;
        bool operator!=(const Function& other) const;
    };
}
