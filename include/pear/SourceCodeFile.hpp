#pragma once

#include <string>
#include <fstream>

namespace pear {
    class SourceCodeFile {
    public:
        SourceCodeFile(const std::string& filename);
        
        bool isOk() const;
        std::string loadContent();

    private:
        std::string filename;
        std::ifstream file;
    };
}
