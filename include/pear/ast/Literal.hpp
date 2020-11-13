#pragma once

#include <pear/ast/Term.hpp>

namespace pear::ast {
    template <typename T>
    class Literal : public Term {
    public:
        Literal(T value) :
            value(value)
        {
        }

        T getValue() const {
            return value;
        }

    private:
        T value;
    };
}

