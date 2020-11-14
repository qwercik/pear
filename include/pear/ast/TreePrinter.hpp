#pragma once

#include <iostream>
#include <pear/ast/NodePrinter.hpp>
#include <pear/ast/AbstractSyntaxTree.hpp>

namespace pear::ast {
    class TreePrinter : public NodePrinter {
    public:
        TreePrinter(const AbstractSyntaxTree& tree);
        friend std::ostream& operator<<(std::ostream& stream, const TreePrinter& node);

    private:
        AbstractSyntaxTree tree;
    };
}
