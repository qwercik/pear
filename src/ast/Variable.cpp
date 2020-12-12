#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>

namespace pear::ast {
    Variable::Variable(const lexer::Lexeme& lexeme) :
        Term(lexeme)
    {
    }
   
    std::string Variable::getName() const {
        return this->getLexeme().getContent();
    }

    void Variable::accept(TermVisitor *visitor) {
        visitor->visit(this);
    }
    
    Term::Pointer Variable::clone() const {
        return std::make_shared<Variable>(*this);
    }
    
    bool Variable::operator==(const Variable& variable) const {
        return this->getName() == variable.getName();
    }

    bool Variable::operator!=(const Variable& variable) const {
        return !(*this == variable);
    }
}

