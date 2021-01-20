#include <pear/pearlog/SideUnification.hpp>
#include <pear/pearlog/UnificationException.hpp>
#include <pear/pearlog/Substitution.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/LexemePosition.hpp>
#include <iostream>
#include <pear/ast/TermPrinter.hpp>


namespace pear::pearlog {
    const std::list<Substitution>& SideUnification::Result::getSubstitutions() const {
        return this->substitutions;
    }

    const ast::Term::Pointer& SideUnification::Result::getTerm() const {
        // It doesn't matter whether we return first or second token
        // If unification goes correctly, they will be the same
        return this->first;
    }

    SideUnification::SideUnification(const ast::Term::Pointer& first, const ast::Term::Pointer& second)
    {
        this->result.first = first->clone();
        this->result.second = second->clone();

        unifyBackend(this->result.first, this->result.second);
    }

    const SideUnification::Result& SideUnification::getResult() const {
        return this->result;
    }

    void SideUnification::unifyBackend(const ast::Term::Pointer& first, const ast::Term::Pointer& second) {
        if (first->getType() == ast::Term::Type::VARIABLE) {
            if (second->getType() != ast::Term::Type::VARIABLE || *first != *second) {
                auto substitution = Substitution(first, second);
                substitution.apply(this->result.first);
                substitution.apply(this->result.second);

                for (auto& other : this->result.substitutions) {
                    substitution.apply(other);
                }

                this->result.substitutions.push_back(substitution);
            }
        } else if (first->getType() == ast::Term::Type::FUNCTION) {
            if (second->getType() == ast::Term::Type::LITERAL) {
                throw UnificationException("Unification error");
            } else if (second->getType() == ast::Term::Type::FUNCTION) {
                if (first->getLexeme().getContent() != second->getLexeme().getContent()) {
                    throw UnificationException("Unification error");
                } else {
                    auto firstIt = first->getChildren().begin();
                    auto firstEnd = first->getChildren().end();
                    auto secondIt = second->getChildren().begin();
                    auto secondEnd = second->getChildren().end();

                    while (firstIt != firstEnd && secondIt != secondEnd) {
                        SideUnification::unifyBackend(*firstIt, *secondIt);
                        firstIt++;
                        secondIt++;
                    }

                    if (firstIt != firstEnd || secondIt != secondEnd) {
                        throw UnificationException("Unification error");
                    }
                }
            }
        }
    }
}
