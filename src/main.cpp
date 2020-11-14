#include <iostream>
#include <algorithm>
#include <fstream>
#include <pear/lexer/Lexer.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/TokenType.hpp>
#include <pear/ast/AbstractSyntaxTree.hpp>
#include <pear/ast/Node.hpp>
#include <pear/parser/Parser.hpp>

void printAst(const pear::ast::Node *node) {
    if (node->getType() == pear::ast::Node::Type::VARIABLE) {
        std::cout << node->getLexeme().getRawCode();
    } else if (node->getType() == pear::ast::Node::Type::LITERAL) {
        std::cout << node->getLexeme().getRawCode();
    } else {
        std::cout << node->getLexeme().getRawCode() << "(";
        
        auto children = node->getChildren();
        if (!children.empty()) {
            auto it = children.begin();
            printAst(it->get());
            it++;

            for (; it != children.end(); it++) {
                std::cout << ", ";
                printAst(it->get());
            }
        }

        std::cout << ")";
    }
}

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

    printAst(&ast);
    std::cout << '\n';
}

