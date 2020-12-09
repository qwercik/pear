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
        visitor->visitVariable(this);
    }
    
    bool Variable::operator==(const Variable& variable) const {
        return this->getName() == variable.getName();
    }
}

