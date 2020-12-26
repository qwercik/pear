#pragma once

#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Term {
    public:
        using Pointer = std::unique_ptr<Term>;

        enum class Type {
            VARIABLE,
            FUNCTION,
            LITERAL
        };

        Term(Type type, const lexer::Lexeme& lexeme);
        Term(const Term& term);

        Term *replace(Pointer&& term);
        Term *addNextChild(Pointer&& child);
        std::list<Term*> getChildren() const;
        std::list<Pointer>&& moveChildren();

        bool hasParent() const;
        Term *getParent() const;

        const lexer::Lexeme& getLexeme() const;
        Type getType() const;

        bool operator==(const Term& term) const;
        bool operator!=(const Term& term) const;

    private:
        void insertChild(const std::list<Pointer>::iterator& iterator, Pointer&& child);
        void dropChild(const std::list<Pointer>::iterator& iterator);

        Type type;
        lexer::Lexeme lexeme;
        std::list<Pointer> children;

        Term *parent = nullptr;
        std::list<Pointer>::iterator parentListIterator;
    };
}
