#include <iostream>
#include <fstream>
#include <pear/lexer/Lexer.hpp>
#include <pear/lexer/Lexeme.hpp>

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

    for (const auto& lexeme : lexemes) {
        if (lexeme.getToken().isWhitespace()) continue;

        std::cout << "\"" << lexeme.getToken().getDescription() << "\": " << ' ' << lexeme.getContent() << '\n';
    }
}

