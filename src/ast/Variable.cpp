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
}

