cmake_minimum_required(VERSION 2.8.11)
project(pear)

add_executable(pear
    src/main.cpp

    include/pear/lexer/Lexer.hpp
    include/pear/lexer/LexerException.hpp
    include/pear/lexer/Token.hpp
    include/pear/lexer/Lexeme.hpp
    include/pear/lexer/LexemePrinter.hpp
    include/pear/lexer/LexemePosition.hpp
    src/lexer/Lexer.cpp
    src/lexer/Token.cpp
    src/lexer/Lexeme.cpp
    src/lexer/LexemePrinter.cpp
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
    include/pear/pearlog/SideUnification.hpp
    include/pear/pearlog/PredicatesManager.hpp
    include/pear/pearlog/Predicate.hpp
    include/pear/pearlog/BuiltinPredicate.hpp
    include/pear/pearlog/RuntimeDefinedPredicate.hpp
    src/pearlog/Interpreter.cpp
    src/pearlog/Substitution.cpp
    src/pearlog/Unification.cpp
    src/pearlog/SideUnification.cpp
    src/pearlog/Predicate.cpp
    src/pearlog/PredicatesManager.cpp
    src/pearlog/RuntimeDefinedPredicate.cpp

    include/pear/pearlog/predicates/Module.hpp
    include/pear/pearlog/predicates/Print.hpp
    include/pear/pearlog/predicates/False.hpp
    include/pear/pearlog/predicates/True.hpp
    include/pear/pearlog/predicates/And.hpp
    include/pear/pearlog/predicates/Or.hpp
    include/pear/pearlog/predicates/Call.hpp
    include/pear/pearlog/predicates/Unify.hpp
    src/pearlog/predicates/Module.cpp
    src/pearlog/predicates/Print.cpp
    src/pearlog/predicates/False.cpp
    src/pearlog/predicates/True.cpp
    src/pearlog/predicates/And.cpp
    src/pearlog/predicates/Or.cpp
    src/pearlog/predicates/Call.cpp
    src/pearlog/predicates/Unify.cpp
)
target_include_directories(pear PUBLIC include/)

target_compile_features(pear PRIVATE cxx_std_17)
