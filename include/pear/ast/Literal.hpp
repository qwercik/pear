#pragma once

#include <string>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Term.hpp>

namespace pear::ast {
    template <typename T>
    class Literal : public Term {
    public:
        Literal(lexer::Lexeme& lexeme) :
            Term(lexeme),
        {
            this->value = this->parse(this->getLexeme().getContent());
        }

        T getValue() const {
            return value;
        }

    private:
        T parse(const std::string& string);

        T value;
    };

    template <>
    std::string Literal<std::string>::parse(const std::string& string) {
        return string;
    }

    template <>
    int Literal<int>::parse(const std::string& string) {
        return std::stoi(string);
    }

    template <>
    double Literal<double>::parse(const std::string& string) {
        return std::stod(string);
    }
}

