#ifndef GENESEQUENCE_H
#define GENESEQUENCE_H

#include <string>

class GeneSequence {
    public:
        GeneSequence();
        ~GeneSequence();
        void appendSequence(std::string sequence);

    private:
        std::string sequence;
};

#endif // GENESEQUENCE_H
