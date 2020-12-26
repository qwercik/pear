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
        VariableVisitor visitor(variable, this->result);
        this->term->accept(&visitor);
    }

    void Unification::UnificationVisitor::visit(ast::Literal *literal) {
        LiteralVisitor visitor(literal, this->result);
        this->term->accept(&visitor);
    }

    void Unification::UnificationVisitor::visit(ast::Function *function) {
        FunctionVisitor visitor(function, this->result);
        this->term->accept(&visitor);
    }



    Unification::VariableVisitor::VariableVisitor(ast::Variable *variable, Unification::Result *result) :
        variable(variable),
        result(result)
    {
    }

    void Unification::VariableVisitor::visit(ast::Variable *variable) {
        if (this->variable != variable) {
            auto newSubstitution = Substitution(this->variable, variable);
            newSubstitution.apply(this->result->substitutions);
            newSubstitution.apply(this->result->term);
        }
    }

    void Unification::VariableVisitor::visit(ast::Literal *literal) {
        auto newSubstitution = Substitution(this->variable, literal);
        newSubstitution.apply(this->result->substitutions);
        newSubstitution.apply(this->result->term);
    }

    void Unification::VariableVisitor::visit(ast::Function *function) {
        auto newSubstitution = Substitution(this->variable, function);
        newSubstitution.apply(this->result->substitutions);
        newSubstitution.apply(this->result->term);
    }  



    Unification::LiteralVisitor::LiteralVisitor(ast::Literal *literal, Unification::Result *result) :
        literal(literal),
        result(result)
    {
    }

    void Unification::LiteralVisitor::visit(ast::Variable *variable) {
        auto newSubstitution = Substitution(variable, this->literal);
        newSubstitution.apply(this->result->substitutions);
        newSubstitution.apply(this->result->term);
    }

    void Unification::LiteralVisitor::visit(ast::Literal *literal) {
        if (*this->literal != *literal) {
            this->result->error = true;
        }
    }

    void Unification::LiteralVisitor::visit(ast::Function *function) {
        this->result->error = false;
    }



    Unification::FunctionVisitor::FunctionVisitor(ast::Function *function, Unification::Result *result) :
        function(function),
        result(result)
    {
    }

    void Unification::FunctionVisitor::visit(ast::Variable *variable) {
        auto newSubstitution = Substitution(variable, this->function);
        newSubstitution.apply(this->result->substitutions);
        newSubstitution.apply(this->result->term);
    }

    void Unification::FunctionVisitor::visit(ast::Literal *literal) {
        this->result->error = true;
    }

    void Unification::FunctionVisitor::visit(ast::Function *function) {
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
        second(second),
        result(first)
    {
        UnificationVisitor visitor(second, &this->result);
        first->accept(&visitor);
    }
    
    Unification::Result Unification::getResult() const {
        return this->result;
    }
}
