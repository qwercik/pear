#include <pear/pearlog/Unification.hpp>
#include <pear/pearlog/Substitution.hpp>
#include <pear/lexer/Lexeme.hpp>
#include <pear/lexer/LexemePosition.hpp>
#include <iostream>


namespace pear::pearlog {
    Unification::Result::Result(const Unification::Result& result) :
        error(result.error),
        substitutions(result.substitutions),
        term(result.term ? result.term->clone() : nullptr) 
    {
    }

    const std::list<Substitution>& Unification::Result::getSubstitutions() const {
        return this->substitutions;
    }

    ast::Term *Unification::Result::getTerm() const {
        return this->term.get();
    }

    bool Unification::Result::isOk() const {
        return !this->error;
    }


    Unification::Unification(const ast::Term::Pointer& first, const ast::Term::Pointer& second) :
        first(first->clone()),
        second(second->clone())
    {
        unifyBackend(this->first, this->second);
        this->result.term = std::move(this->first);
    }

    const Unification::Result& Unification::getResult() const {
        return this->result;
    }

    void Unification::unifyBackend(const ast::Term::Pointer& first, const ast::Term::Pointer& second) {
        if (first->getType() == ast::Term::Type::VARIABLE) {
            if (second->getType() != ast::Term::Type::VARIABLE || *first != *second) {
                auto substitution = Substitution(first, second);
                substitution.apply(this->first);
                substitution.apply(this->second);

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
                    this->result.error = true;
                    // Maybe throw an exception?
                }
            } else {
                this->result.error = true;
            }
        } else {
            if (second->getType() == ast::Term::Type::VARIABLE) {
                this->unifyBackend(second, first);
            } else if (second->getType() == ast::Term::Type::LITERAL) {
                this->result.error = true;
            } else {
                if (first->getLexeme().getContent() != second->getLexeme().getContent()) {
                    this->result.error = true;
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

                    if (firstIt != firstEnd && secondIt != secondEnd) {
                        result.error = true;
                    }
                }
            }
        }
    }
}
