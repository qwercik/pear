cmake_minimum_required(VERSION 2.8.11)
project(pear)

add_executable(pear
    src/main.cpp

    include/pear/lexer/Lexer.hpp
    include/pear/lexer/LexerException.hpp
    include/pear/lexer/Token.hpp
    include/pear/lexer/Lexeme.hpp
    include/pear/lexer/LexemePosition.hpp
    src/lexer/Lexer.cpp
    src/lexer/Token.cpp
    src/lexer/Lexeme.cpp
    src/lexer/LexemePosition.cpp

    include/pear/ast/Node.hpp
    include/pear/ast/NodePrinter.hpp
    src/ast/Node.cpp
    src/ast/NodePrinter.cpp

    include/pear/parser/Parser.hpp
    include/pear/parser/ParserException.hpp
    src/parser/Parser.cpp
)
target_include_directories(pear PUBLIC include/)

target_compile_features(pear PRIVATE cxx_std_17)
