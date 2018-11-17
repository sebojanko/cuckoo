#ifndef FASTADOCUMENT_H
#define FASTADOCUMENT_H

#include <string>
#include <fstream>

class FastADocument {
    public:
        FastADocument(std::string filename);
        ~FastADocument();
        std::string GetNextSequence();
        std::string GetFileName() { return filename_; }
    private:
        std::string filename_;
        std::ifstream *input_;
};

#endif // FASTADOCUMENT_H
