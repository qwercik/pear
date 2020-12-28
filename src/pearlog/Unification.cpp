#include <pear/pearlog/Unification.hpp>
#include <pear/pearlog/UnificationException.hpp>
#include <pear/pearlog/Substitution.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/LexemePosition.hpp>
#include <iostream>
#include <pear/ast/TermPrinter.hpp>


namespace pear::pearlog {
    const std::list<Substitution>& Unification::Result::getSubstitutions() const {
        return this->substitutions;
    }

    const ast::Term::Pointer& Unification::Result::getTerm() const {
        // It doesn't matter whether we return first or second token
        // If unification goes correctly, they will be the same
        return this->first;
    }

    Unification::Unification(const ast::Term::Pointer& first, const ast::Term::Pointer& second)
    {
        this->result.first = first->clone();
        this->result.second = second->clone();

        unifyBackend(this->result.first, this->result.second);
    }

    const Unification::Result& Unification::getResult() const {
        return this->result;
    }

    void Unification::unifyBackend(const ast::Term::Pointer& first, const ast::Term::Pointer& second) {
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
        } else if (first->getType() == ast::Term::Type::LITERAL) {
            if (second->getType() == ast::Term::Type::VARIABLE) {
                this->unifyBackend(second, first);
            } else if (second->getType() == ast::Term::Type::LITERAL) {
                if (*first != *second) {
                    throw UnificationException("Unification error");
                }
            } else {
                throw UnificationException("Unification error");
            }
        } else {
            if (second->getType() == ast::Term::Type::VARIABLE) {
                this->unifyBackend(second, first);
            } else if (second->getType() == ast::Term::Type::LITERAL) {
                throw UnificationException("Unification error");
            } else {
                if (first->getLexeme().getContent() != second->getLexeme().getContent()) {
                    throw UnificationException("Unification error");
                } else {
                    auto firstIt = first->getChildren().begin();
                    auto firstEnd = first->getChildren().end();
                    auto secondIt = second->getChildren().begin();
                    auto secondEnd = second->getChildren().end();

                    while (firstIt != firstEnd && secondIt != secondEnd) {
                        Unification::unifyBackend(*firstIt, *secondIt);
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
