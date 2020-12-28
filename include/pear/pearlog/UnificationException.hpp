#pragma once

#include <string>
#include <stdexcept>

namespace pear::pearlog {
    class UnificationException : public std::runtime_error {
    public:
        UnificationException(const std::string& message) :
            std::runtime_error(message)
        {
        }
    };
}
