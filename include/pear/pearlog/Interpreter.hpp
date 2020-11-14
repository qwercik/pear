#pragma once

#include <pear/Executor.hpp>
#include <pear/ast/Tree.hpp>

namespace pear::pearlog {
    class Interpreter : public Executor {
    public:
        virtual void execute(ast::Tree& tree) override;
    };
};
