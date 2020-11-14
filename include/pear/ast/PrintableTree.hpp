#pragma once

#include <pear/ast/AbstractSyntaxTree.hpp>
#include <pear/ast/Node.hpp>
#include <iostream>

namespace pear::ast {
    class PrintableTree : public AbstractSyntaxTree {
    public:
        PrintableTree(const AbstractSyntaxTree& tree);
        friend std::ostream& operator<<(std::ostream& stream, const PrintableTree& tree);

    private:
        void print(const Node *node) const;

        AbstractSyntaxTree tree;
    };
}

