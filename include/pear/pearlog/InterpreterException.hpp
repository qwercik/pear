#pragma once

#include <string>
#include <stdexcept>

namespace pear::pearlog {
    class InterpreterException : public std::runtime_error {
    public:
        InterpreterException(const std::string& message) :
            std::runtime_error(message)
        {
        }
    };
}
