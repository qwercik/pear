#pragma once

#include <pear/Executor.hpp>
#include <pear/ast/Node.hpp>

namespace pear::pearlog {
    class Interpreter : public Executor {
    public:
        virtual void execute(ast::Node& tree) override;
    };
};
