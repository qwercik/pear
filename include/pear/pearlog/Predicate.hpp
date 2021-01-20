#pragma once

#include <memory>
#include <pear/ast/Term.hpp>

namespace pear::pearlog {
    class Interpreter;
    class Substitution;

    class Predicate {
    public:
        using Pointer = std::shared_ptr<Predicate>;
        class Instance {
        public:
            virtual bool next() = 0;
            const std::list<Substitution>& getSubstitutions() const;

        private:
            std::list<Substitution> substitutions;
        };

        explicit Predicate(Interpreter& interpreter);

        std::unique_ptr<Instance> createInstance(const ast::Term::Pointer& term) const;
        virtual bool unify(const ast::Term::Pointer& term) const = 0;

    protected:
        virtual std::unique_ptr<Instance> createInstanceBackend(const ast::Term::Pointer& term) const = 0;

        Interpreter& interpreter;
    };
}
