#include <pear/pearlog/Unification.hpp>
#include <pear/pearlog/Substitution.hpp>
#include <iostream>

namespace pear::pearlog {
    Unification::UnificationVisitor::UnificationVisitor(ast::Term *term, Unification::Result *result) :
        term(term),
        result(result)
    {
    }

    void Unification::UnificationVisitor::visit(ast::Variable *variable) {
        std::cerr << "A\n";
        VariableVisitor visitor(variable, this->result);
        this->term->accept(&visitor);
    }

    void Unification::UnificationVisitor::visit(ast::Literal *literal) {
        std::cerr << "B\n";
        LiteralVisitor visitor(literal, this->result);
        this->term->accept(&visitor);
    }

    void Unification::UnificationVisitor::visit(ast::Function *function) {
        std::cerr << "C\n";
        FunctionVisitor visitor(function, this->result);
        this->term->accept(&visitor);
    }



    Unification::VariableVisitor::VariableVisitor(ast::Variable *variable, Unification::Result *result) :
        variable(variable),
        result(result)
    {
    }

    void Unification::VariableVisitor::visit(ast::Variable *variable) {
        std::cerr << "D\n";
        if (this->variable != variable) {
            this->result->substitutions.push_back(Substitution(this->variable, variable));
        }
    }

    void Unification::VariableVisitor::visit(ast::Literal *literal) {
        std::cerr << "E\n";
        this->result->substitutions.push_back(Substitution(this->variable, literal));
    }

    void Unification::VariableVisitor::visit(ast::Function *function) {
        std::cerr << "F\n";
        this->result->substitutions.push_back(Substitution(this->variable, function));
    }  



    Unification::LiteralVisitor::LiteralVisitor(ast::Literal *literal, Unification::Result *result) :
        literal(literal),
        result(result)
    {
    }

    void Unification::LiteralVisitor::visit(ast::Variable *variable) {
        std::cerr << "G\n";
        this->result->substitutions.push_back(Substitution(variable, this->literal));
    }

    void Unification::LiteralVisitor::visit(ast::Literal *literal) {
        std::cerr << "H\n";
        if (this->literal != literal) {
            this->result->error = true;
        }
    }

    void Unification::LiteralVisitor::visit(ast::Function *function) {
        std::cerr << "I\n";
        this->result->error = false;
    }



    Unification::FunctionVisitor::FunctionVisitor(ast::Function *function, Unification::Result *result) :
        function(function),
        result(result)
    {
    }

    void Unification::FunctionVisitor::visit(ast::Variable *variable) {
        std::cerr << "J\n";
        this->result->substitutions.push_back(Substitution(variable, this->function));
    }

    void Unification::FunctionVisitor::visit(ast::Literal *literal) {
        std::cerr << "K\n";
        this->result->error = true;
    }

    void Unification::FunctionVisitor::visit(ast::Function *function) {
        std::cerr << "L\n";
        // Comparing signatures (name and arity)
        if (*this->function != *function) {
            this->result->error = true;
            return;
        }

        auto firstArgs = this->function->getArguments();
        auto secondArgs = function->getArguments();

        auto firstIter = firstArgs.begin();
        auto secondIter = secondArgs.begin();
        while (firstIter != firstArgs.end() && secondIter != secondArgs.end()) {
            auto firstElement = *firstIter;
            auto secondElement = *secondIter;

            UnificationVisitor visitor(secondElement.get(), this->result);
            (firstElement.get())->accept(&visitor);

            if (this->result->error) {
                return;
            }

            firstIter++;
            secondIter++;
        }
    }



    Unification::Unification(ast::Term *first, ast::Term *second) :
        first(first),
        second(second)
    {
        UnificationVisitor visitor(second, &this->result);
        first->accept(&visitor);
    }
    
    Unification::Result Unification::getResult() const {
        return this->result;
    }
}
