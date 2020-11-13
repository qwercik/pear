#include <stdexcept>

namespace pear::parser {
    class ParserException : public std::runtime_error {
    public:
        ParserException(const std::string& message) :
            std::runtime_error(message)
        {
        }
    };
}
