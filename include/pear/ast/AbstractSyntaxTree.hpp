#pragma once

#include <list>
#include <pear/lexer/Lexeme.hpp>
#include <pear/ast/Node.hpp>

namespace pear::ast {
    class AbstractSyntaxTree : public Node {
    public:
        AbstractSyntaxTree();
    };
}
