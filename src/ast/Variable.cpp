#include <string>
#include <pear/ast/Variable.hpp>

namespace pear::ast {
    Variable::Variable(const std::string& name) :
        name(name)
    {
    }
    
    std::string Variable::getName() const {
        return this->name;
    }
}
