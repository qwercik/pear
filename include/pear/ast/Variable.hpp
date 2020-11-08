#pragma once

#include <pear/ast/Term.hpp>

namespace pear::ast {
    class Variable : public Term {
    public:
        Variable(const std::string& name);

        std::string getName() const;

    private:
        std::string name;
    }
}

