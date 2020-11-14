#include <iostream>
#include <pear/pearlog/Interpreter.hpp>
#include <pear/ast/AbstractSyntaxTree.hpp>

namespace pear::pearlog {
    void Interpreter::execute(ast::AbstractSyntaxTree& tree) {
        std::cout << "Wykonuje się program\n";
    }
};
