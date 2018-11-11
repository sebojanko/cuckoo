#ifndef FASTADOCUMENT_H
#define FASTADOCUMENT_H

#include <string>
#include <fstream>

class FastADocument {
    public:
        FastADocument(std::string filename);
        ~FastADocument();
        std::string getNextSequence();
        std::string getFileName() { return filename; }
    private:
        std::string filename;
        std::ifstream *input;
};

#endif // FASTADOCUMENT_H
