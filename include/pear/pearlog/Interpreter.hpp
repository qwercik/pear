#pragma once

#include <pear/Executor.hpp>
#include <pear/ast/AbstractSyntaxTree.hpp>

namespace pear::pearlog {
    class Interpreter : public Executor {
    public:
        virtual void execute(ast::AbstractSyntaxTree& tree) override;
    };
};
