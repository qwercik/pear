#include <iostream>
#include <pear/pearlog/Interpreter.hpp>
#include <pear/ast/Tree.hpp>

namespace pear::pearlog {
    void Interpreter::execute(ast::Tree& tree) {
        std::cout << "Wykonuje się program\n";
    }
};
