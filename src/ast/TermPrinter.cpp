#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermPrinter.hpp>

namespace pear::ast {
    TermPrinter::TermPrinter(const Term *term) :
        term(term)
    {
    }

    void TermPrinter::print(std::ostream& stream, const Term *term) {
        if (term->getType() == Term::Type::VARIABLE) {
            stream << term->getLexeme().getContent();
        } else if (term->getType() == Term::Type::LITERAL) {
            stream << term->getLexeme().getContent();
        } else {
            stream << term->getLexeme().getContent() << "(";

            auto children = term->getChildren();
            if (!children.empty()) {
                auto child = children.begin();
                TermPrinter::print(stream, *child);
                child++;

                for (; child != children.end(); child++) {
                    stream << ", ";
                    TermPrinter::print(stream, *child);
                }
            }

            stream << ")";
        }
    }

    std::ostream& operator<<(std::ostream& stream, const TermPrinter& printer) {
        TermPrinter::print(stream, printer.term);
        return stream;
    }
}

