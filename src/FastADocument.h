#ifndef SRC_FASTADOCUMENT_H_
#define SRC_FASTADOCUMENT_H_

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

#endif  // SRC_FASTADOCUMENT_H_
