#pragma once

#include <list>
#include <memory>
#include <pear/lexer/Lexeme.hpp>

namespace pear::ast {
    class Term {
    public:
        using Pointer = std::unique_ptr<Term>;
        using List = std::list<Pointer>;
        using Iterator = List::iterator;

        enum class Type {
            VARIABLE,
            FUNCTION,
            LITERAL
        };

        Term(Type type, const lexer::Lexeme& lexeme);
        Term(const Term& term);

        void setScopeId(int scopeId);
        void addNextChild(Pointer&& term);
        void replaceChild(Iterator iterator, Pointer&& term);
        void insertChild(Iterator iterator, Pointer&& term);
        Pointer dropChild(Iterator iterator);

        bool hasParent() const;
        Term *getParent();

        Type getType() const;
        int getScopeId() const;
        const lexer::Lexeme& getLexeme() const;
        const List& getChildren() const;
        List& getChildren();
        Iterator getParentListIterator() const;

        bool operator==(const Term& term) const;
        bool operator!=(const Term& term) const;

        Pointer clone() const;

    private:
        Type type;

        // It will be used by interpreter part
        // -1 mean that scopeId doesn't matter
        // non-negative value represents scope id
        int scopeId = -1;

        lexer::Lexeme lexeme;
        std::list<Pointer> children;
        Term *parent = nullptr;
        std::list<Pointer>::iterator parentListIterator;
    };
}
