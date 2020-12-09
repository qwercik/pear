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

    include/pear/ast/Term.hpp
    include/pear/ast/Function.hpp
    include/pear/ast/Variable.hpp
    include/pear/ast/Literal.hpp
    include/pear/ast/TermPrinter.hpp
    src/ast/Term.cpp
    src/ast/Function.cpp
    src/ast/Variable.cpp
    src/ast/TermPrinter.cpp

    include/pear/parser/Parser.hpp
    include/pear/parser/ParserException.hpp
    src/parser/Parser.cpp

    include/pear/pearlog/Interpreter.hpp
    include/pear/pearlog/Substitution.hpp
    include/pear/pearlog/Unification.hpp
    src/pearlog/Interpreter.cpp
    src/pearlog/Substitution.cpp
    src/pearlog/Unification.cpp
)
target_include_directories(pear PUBLIC include/)

target_compile_features(pear PRIVATE cxx_std_17)
