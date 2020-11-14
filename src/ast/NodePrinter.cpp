#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Node.hpp>
#include <pear/ast/NodePrinter.hpp>

namespace pear::ast {
    NodePrinter::NodePrinter(const Node& node) :
        node(node);
    {
    }

    void NodePrinter::print(std::ostream& stream, const Node *node) {
        if (node->isVariable()) {
            stream << node->getLexeme().getContent();
        } else if (node->isLiteral()) {
            stream << node->getLexeme().getContent();
        } else {
            stream << node->getLexeme().getContent() << "(";
            
            auto children = node->getChildren();
            if (!children.empty()) {
                auto it = children.begin();
                NodePrinter::print(stream, it->get());
                it++;

                for (; it != children.end(); it++) {
                    stream << ", ";
                    NodePrinter::print(stream, it->get());
                }
            }

            stream << ")";
        }
    }

    std::ostream& operator<<(std::ostream& stream, const NodePrinter& printer) {
        NodePrinter::print(stream, &printer.node);
        return stream;
    }
}

