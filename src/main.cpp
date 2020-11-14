#include <iostream>
#include <algorithm>
#include <fstream>
#include <pear/lexer/Lexer.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/ast/Tree.hpp>
#include <pear/ast/NodePrinter.hpp>
#include <pear/ast/Node.hpp>
#include <pear/parser/Parser.hpp>
#include <pear/pearlog/Interpreter.hpp>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect usage\n";
        std::cerr << "Use: " << argv[0] << " <path>\n";
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Invalid file\n";
        return 1;
    }

    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    pear::lexer::Lexer lexer(code);
    auto lexemes = lexer.run();

    pear::parser::Parser parser(lexemes);
    auto ast = parser.run();

    pear::pearlog::Interpreter interpreter;
    interpreter.execute(ast);
}

