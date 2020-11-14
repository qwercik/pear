#pragma once

#include <cstddef>

namespace pear::lexer {
    class LexemePosition {
    public:
        friend class Lexeme;

        std::size_t getOffset() const;
        std::size_t getLineNumber() const;
        std::size_t getColumnNumber() const;
    
    private:
        std::size_t offset = 0;
        std::size_t lineNumber = 1;
        std::size_t columnNumber = 1;
    };
}
