#pragma once

#include <pear/Executor.hpp>
#include <pear/ast/Term.hpp>

namespace pear::pearlog {
    class Interpreter : public Executor {
    public:
        virtual void execute(const ast::Term::Pointer& term) override;
    };
};
