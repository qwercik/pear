#include <pear/lexer/LexemePosition.hpp>
#include <pear/lexer/Token.hpp>

namespace pear::lexer {
    std::size_t LexemePosition::getOffset() const {
        return this->offset;
    }

    std::size_t LexemePosition::getLineNumber() const {
        return this->lineNumber;
    }

    std::size_t LexemePosition::getColumnNumber() const {
        return this->columnNumber;
    }
}
