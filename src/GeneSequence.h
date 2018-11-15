#ifndef GENESEQUENCE_H
#define GENESEQUENCE_H

#include <string>

class GeneSequence {
    public:
        GeneSequence();
        ~GeneSequence();
        void AppendSequence(std::string sequence);

    private:
        std::string sequence_;
};

#endif // GENESEQUENCE_H
