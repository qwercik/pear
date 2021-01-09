#pragma once

#include <pear/lexer/Lexeme.hpp>

namespace pear::lexer {
    class LexemePrinter {
    public:
        LexemePrinter(const Lexeme& lexeme);
        friend std::ostream& operator<<(std::ostream& stream, const LexemePrinter& lexemePrinter);

    protected:
        static void print(std::ostream& ostream, const Lexeme& lexeme);

    private:
        const Lexeme& lexeme;
    };
}