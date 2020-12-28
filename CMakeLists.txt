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
    include/pear/ast/TermPrinter.hpp
    src/ast/Term.cpp
    src/ast/TermPrinter.cpp

    include/pear/parser/Parser.hpp
    include/pear/parser/ParserException.hpp
    src/parser/Parser.cpp

    include/pear/pearlog/Interpreter.hpp
    include/pear/pearlog/Substitution.hpp
    include/pear/pearlog/Unification.hpp
    include/pear/pearlog/PredicatesManager.hpp
    src/pearlog/Interpreter.cpp
    src/pearlog/Substitution.cpp
    src/pearlog/Unification.cpp
    src/pearlog/PredicatesManager.cpp

    include/pear/pearlog/predicates/Print.hpp
    include/pear/pearlog/predicates/False.hpp
    include/pear/pearlog/predicates/True.hpp
    src/pearlog/predicates/Print.cpp
    src/pearlog/predicates/False.cpp
    src/pearlog/predicates/True.cpp
)
target_include_directories(pear PUBLIC include/)

target_compile_features(pear PRIVATE cxx_std_17)
