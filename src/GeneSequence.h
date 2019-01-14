#ifndef SRC_GENESEQUENCE_H_
#define SRC_GENESEQUENCE_H_

#include <string>

class GeneSequence {
 public:
    GeneSequence();
    ~GeneSequence();
    void AppendSequence(std::string sequence);

 private:
    std::string sequence_;
};

#endif  // SRC_GENESEQUENCE_H_
