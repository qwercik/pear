#pragma once

#include <iostream>
#include <pear/ast/Node.hpp>

namespace pear::ast {
    class NodePrinter {
    public:
        NodePrinter(const Node& node);
        friend std::ostream& operator<<(std::ostream& stream, const NodePrinter& node);

    protected:
        static void print(std::ostream& stream, const Node *node);

    private:
        Node node;
    };
}

