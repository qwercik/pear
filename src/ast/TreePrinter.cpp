#include <pear/ast/TreePrinter.hpp>

namespace pear::ast {
    TreePrinter::TreePrinter(const Tree& tree) :
        tree(tree)
    {
    }

    std::ostream& operator<<(std::ostream& stream, const TreePrinter& printer) {
        TreePrinter::print(stream, &tree.tree.root);
        return stream;
    }
}

