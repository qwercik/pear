#include <iostream>
#include <pear/ast/AbstractSyntaxTree.hpp>
#include <pear/ast/Node.hpp>
#include <pear/ast/PrintableTree.hpp>

namespace pear::ast {
    PrintableTree::PrintableTree(const AbstractSyntaxTree& tree) :
        tree(tree)
    {
    }

    void PrintableTree::print(const Node *node) const {
        if (node->getType() == pear::ast::Node::Type::VARIABLE) {
            std::cout << node->getLexeme().getRawCode();
        } else if (node->getType() == pear::ast::Node::Type::LITERAL) {
            std::cout << node->getLexeme().getRawCode();
        } else {
            std::cout << node->getLexeme().getRawCode() << "(";
            
            auto children = node->getChildren();
            if (!children.empty()) {
                auto it = children.begin();
                this->print(it->get());
                it++;

                for (; it != children.end(); it++) {
                    std::cout << ", ";
                    this->print(it->get());
                }
            }

            std::cout << ")";
        }
    }

    std::ostream& operator<<(std::ostream& stream, const PrintableTree& tree) {
        tree.print(&tree.tree);
        return stream;
    }
}

