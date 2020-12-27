#pragma once

#include <memory>
#include <pear/ast/Term.hpp>
#include <pear/ast/Variable.hpp>

namespace pear::pearlog {
    class Substitution {
    public:
        Substitution(const ast::Term *destination, const ast::Term *source);
        Substitution(const Substitution& substitution);

        void apply(ast::Term *term) const;
        void apply(Substitution &substitution) const;
 
        const ast::Term *getDestination() const;
        const ast::Term *getSource() const;

    private:
        std::unique_ptr<ast::Term> destination;
        std::unique_ptr<ast::Term> source;
    };
}
