#include <pear/pearlog/Substitution.hpp>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>
#include <pear/ast/Function.hpp>
#include <pear/ast/Literal.hpp>

namespace pear::pearlog {
    Substitution::Substitution(const ast::Variable *variable, const ast::Term *other) :
        variable(variable),
        other(other)
    {
    }

    void Substitution::apply(ast::Term* term) {
        term->accept(this);
    }

    void Substitution::visitVariable(ast::Variable* variable) {
        if (*this->variable == *variable) {
            variable->replace(new ast::Variable(*this->variable));
        }
    }
    
    void Substitution::visitLiteral(ast::Literal* literal) {
    }

    void Substitution::visitFunction(ast::Function* function) {
        for (auto& child : function->getArguments()) {
            this->apply(child.get());
        }
    }
}

