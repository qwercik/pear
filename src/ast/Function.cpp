#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Function.hpp>

namespace pear::ast {
    Function::Function(const lexer::Lexeme& lexeme) :
        Term(lexeme)
    {
    }
    
    std::string Function::getName() const {
        return this->getLexeme().getContent();
    }

    Term::List Function::getArguments() const {
        return this->getChildren();
    }

    std::size_t Function::getArity() const {
        return this->getArguments().size();
    }
    
    void Function::accept(TermVisitor *visitor) {
        visitor->visitFunction(this);
    }
    
    bool Function::operator==(const Function& other) const {
        return this->getArity() == other.getArity() && this->getName() == other.getName();
    }
}
