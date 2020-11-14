#pragma once

#include <stdexcept>

namespace pear::lexer {
    class LexerException : public std::runtime_error {
    public:
        LexerException(const std::string& message) :
            std::runtime_error(message)
        {
        }
    };
}

