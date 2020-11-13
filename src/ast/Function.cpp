#include <string>
#include <pear/ast/Function.hpp>

namespace pear::ast {
    Function::Function(const std::string& name) :
        name(name)
    {
    }
    
    std::string Function::getName() const {
        return this->name;
    }

    void Function::addArgument(const Term& term) {
        this->arguments.push_back(term);
    }

    std::list<Term> Function::getArguments() const {
        return this->arguments;
    }
}

