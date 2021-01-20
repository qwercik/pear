#pragma once

#include <pear/pearlog/Predicate.hpp>

namespace pear::pearlog {
    class BuiltinPredicate : public Predicate {
    public:
        BuiltinPredicate(Interpreter& interpreter) :
            Predicate(interpreter)
        {
        }

        class Instance : public Predicate::Instance {
        };
    };
}
