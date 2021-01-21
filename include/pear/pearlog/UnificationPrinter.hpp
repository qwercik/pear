#pragma once

#include <iostream>
#include <pear/pearlog/Unification.hpp>

namespace pear::pearlog {
    class UnificationPrinter {
    public:
        explicit UnificationPrinter(const Unification::Result& result);
        friend std::ostream& operator<<(std::ostream& stream, const UnificationPrinter& printer);

    private:
        const Unification::Result& result;
    };
}

