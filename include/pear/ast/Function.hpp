#pragma once

#include <list>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    class Function : public Term {
    public:
        Function(const std::string& name);

        std::string getName() const;

        void addArgument(const Term& term);
        std::list<Term> getArguments() const;

    private:
        std::string name;
        std::list<Term> arguments;
    }
}

