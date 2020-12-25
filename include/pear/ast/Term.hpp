#pragma once

#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/TermVisitor.hpp>

namespace pear::ast {
    class Term {
    public:
        using Pointer = std::shared_ptr<Term>;
        using List = std::list<Pointer>;
        using Iterator = List::iterator;

        Term() = default;
        Term(const lexer::Lexeme& lexeme);
        Term(const Term& term);

        const lexer::Lexeme& getLexeme() const;

        bool hasParent() const;
        Term *getParent() const;

        Term *addNextChild(std::shared_ptr<Term> child);
        const List& getChildren() const;

        bool isVariable() const;
        bool isLiteral() const;
        bool isFunction() const;

        void replace(std::shared_ptr<Term> term);

        virtual void accept(TermVisitor *visitor) = 0;
        virtual Pointer clone() const = 0;

    private:
        void insertChild(const Iterator& iterator, std::shared_ptr<Term> child);
        void dropChild(const Iterator& iterator);

        lexer::Lexeme lexeme;
        Term *parent = nullptr;
        Iterator parentListIterator;
        List children;
    };
}
