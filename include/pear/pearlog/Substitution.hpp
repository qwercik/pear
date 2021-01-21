#pragma once

#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>

namespace pear::pearlog {
    class Substitution {
    public:
        Substitution(const ast::Term::Pointer& destination, const ast::Term::Pointer& source);
        Substitution(const Substitution& substitution);

        void apply(ast::Term::Pointer& term) const;
        void apply(Substitution& substitution) const;
 
        ast::Term::Pointer& getDestination();
        const ast::Term::Pointer& getDestination() const;
        ast::Term::Pointer& getSource();
        const ast::Term::Pointer& getSource() const;

    private:
        std::unique_ptr<ast::Term> destination;
        std::unique_ptr<ast::Term> source;
    };
}
