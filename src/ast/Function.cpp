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

    auto Function::getArguments() const {
        return this->getChildren();
    }

    std::size_t Function::getArity() const {
        return this->getArguments().size();
    }
}
