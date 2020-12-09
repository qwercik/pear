#include <pear/pearlog/Unification.hpp>

namespace pear::pearlog {
    Unification::Unification(const ast::Term *first, const ast::Term *second) :
        first(first),
        second(second)
    {
        
    }


    std::list<Substitution> Unification::getSubstitutions() const {
        return this->substitutions;
    }
}
