#include <pear/pearlog/Interpreter.hpp>
#include <pear/ast/Term.hpp>
#include <pear/pearlog/predicates/Module.hpp>
#include <pear/pearlog/InterpreterException.hpp>
#include <pear/pearlog/predicates/Module.hpp>
#include <pear/pearlog/predicates/Call.hpp>
#include <pear/pearlog/predicates/True.hpp>
#include <pear/pearlog/predicates/False.hpp>
#include <pear/pearlog/predicates/Eval.hpp>
#include <iostream>
#include <pear/ast/TermPrinter.hpp>

namespace pear::pearlog {
    Interpreter::Interpreter() {
        this->predicatesManager.insertBack(std::make_unique<predicates::Module>());
        //this->predicatesManager.insertBack(std::make_unique<predicates::Call>());
        this->predicatesManager.insertBack(std::make_unique<predicates::False>());
        this->predicatesManager.insertBack(std::make_unique<predicates::True>());
        //this->predicatesManager.insertBack(std::make_unique<predicates::Eval>());
    }

    bool Interpreter::execute(const ast::Term::Pointer& term) {
        std::list<Substitution> substitutions;
        return this->execute(term, substitutions);
    }

    bool Interpreter::execute(const ast::Term::Pointer& term, std::list<Substitution>& substitutions) {
        auto iterator = this->predicatesManager.getStart();

        bool result = false;
        while (true) {
            std::list<Substitution> substitutionsCopy = substitutions;
            if (!this->predicatesManager.executeNext(iterator, *this, term, substitutionsCopy)) {
                break;
            }

            result = true;
        }

        return result;
    }
};
