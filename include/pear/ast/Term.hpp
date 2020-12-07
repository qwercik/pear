#pragma once

#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Term {
    public:
        using Pointer = std::shared_ptr<Term>;

        Term() = default;
        Term(const lexer::Lexeme& lexeme);

        const lexer::Lexeme& getLexeme() const;

        bool hasParent() const;
        Term *getParent() const;

        Term *addNextChild(Term *child);
        const std::list<Pointer>& getChildren() const;

        bool isVariable() const;
        bool isLiteral() const;
        bool isFunction() const;

    private:
        lexer::Lexeme lexeme;
        Term *parent = nullptr;
        std::list<Pointer> children;
    };
}
