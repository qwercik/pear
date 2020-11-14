#pragma once

#include <iostream>
#include <pear/ast/NodePrinter.hpp>
#include <pear/ast/Tree.hpp>

namespace pear::ast {
    class TreePrinter : public NodePrinter {
    public:
        TreePrinter(const Tree& tree);
        friend std::ostream& operator<<(std::ostream& stream, const TreePrinter& node);

    private:
        Tree tree;
    };
}
