#pragma once

namespace pear::ast {
    template <typename T>
    class Visitable {
    public:
        virtual T* accept(T *visitable) = 0;
    };
};
