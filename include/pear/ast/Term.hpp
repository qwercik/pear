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

        void addNextChild(Pointer&& term);
        void replaceChild(std::list<Pointer>::iterator iterator, Pointer&& term);
        void insertChild(std::list<Pointer>::iterator iterator, Pointer&& term);
        Pointer dropChild(std::list<Pointer>::iterator iterator);

        bool hasParent() const;
        Term *getParent() const;
        Type getType() const;
        const lexer::Lexeme& getLexeme() const;
        std::list<Term*> getChildren() const;
        std::list<Pointer>::iterator getParentListIterator() const;

        bool operator==(const Term& term) const;
        bool operator!=(const Term& term) const;

    private:
        Type type;
        lexer::Lexeme lexeme;
        std::list<Pointer> children;
        Term *parent = nullptr;
        std::list<Pointer>::iterator parentListIterator;
    };
}
