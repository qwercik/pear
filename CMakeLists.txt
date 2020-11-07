cmake_minimum_required(VERSION 2.8.11)
project(pear)

add_executable(pear
    src/main.cpp

    include/pear/lexer/Lexer.hpp
    include/pear/lexer/Token.hpp
    include/pear/lexer/Lexeme.hpp
    src/lexer/Lexer.cpp
    src/lexer/Token.cpp
    src/lexer/Lexeme.cpp
)
target_include_directories(pear PUBLIC include/)

target_compile_features(pear PRIVATE cxx_std_17)
