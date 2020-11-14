cmake_minimum_required(VERSION 2.8.11)
project(pear)

add_executable(pear
    src/main.cpp

    include/pear/lexer/Lexer.hpp
    include/pear/lexer/Token.hpp
    include/pear/lexer/TokenType.hpp
    include/pear/lexer/Lexeme.hpp
    src/lexer/Lexer.cpp
    src/lexer/Token.cpp
    src/lexer/TokenType.cpp
    src/lexer/Lexeme.cpp

    include/pear/ast/Tree.hpp
    include/pear/ast/Node.hpp
    include/pear/ast/NodePrinter.hpp
    src/ast/Tree.cpp
    src/ast/Node.cpp
    src/ast/NodePrinter.cpp

    include/pear/parser/Parser.hpp
    include/pear/parser/ParserException.hpp
    src/parser/Parser.cpp

    include/pear/Executor.hpp
    include/pear/pearlog/Interpreter.hpp
    src/pearlog/Interpreter.cpp
)
target_include_directories(pear PUBLIC include/)

target_compile_features(pear PRIVATE cxx_std_17)
