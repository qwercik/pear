#pragma once

#include <pear/ast/Tree.hpp>
#include <pear/ast/Node.hpp>
#include <iostream>

namespace pear::ast {
    class PrintableTree : public Tree {
    public:
        PrintableTree(const Tree& tree);
        friend std::ostream& operator<<(std::ostream& stream, const PrintableTree& tree);

    private:
        void print(const Node *node) const;

        Tree tree;
    };
}

