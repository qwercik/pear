#include <string>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/TermVisitor.hpp>
#include <pear/ast/Literal.hpp>

namespace pear::ast {
    Literal::Literal(const lexer::Lexeme& lexeme) :
        Term(lexeme)
    {
    }

    std::string Literal::getContent() const {
        return this->getLexeme().getContent();
    }

    void Literal::accept(TermVisitor *visitor) {
        visitor->visit(this);
    }
    
    Term::Pointer Literal::clone() const {
        return std::make_shared<Literal>(*this);
    }

    bool Literal::operator==(const Literal& literal) const {
        return this->getContent() == literal.getContent();
    }
    
    bool Literal::operator!=(const Literal& literal) const {
        return !(*this == literal);
    }
}
