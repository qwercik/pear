#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>

namespace pear::ast {
    TermPrinter::TermPrinter(const Term& node) :
        node(node)
    {
    }

    void TermPrinter::print(std::ostream& stream, const Term *node) {
        if (node->isVariable()) {
            stream << node->getLexeme().getContent();
        } else if (node->isLiteral()) {
            stream << node->getLexeme().getContent();
        } else {
            stream << node->getLexeme().getContent() << "(";
            
            auto children = node->getChildren();
            if (!children.empty()) {
                auto it = children.begin();
                TermPrinter::print(stream, it->get());
                it++;

                for (; it != children.end(); it++) {
                    stream << ", ";
                    TermPrinter::print(stream, it->get());
                }
            }

            stream << ")";
        }
    }

    std::ostream& operator<<(std::ostream& stream, const TermPrinter& printer) {
        TermPrinter::print(stream, &printer.node);
        return stream;
    }
}

