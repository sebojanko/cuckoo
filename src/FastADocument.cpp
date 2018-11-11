#include "FastADocument.h"

FastADocument::FastADocument(std::string filename) : filename(filename) {
    input = new std::ifstream();
    input->open(filename);
}

FastADocument::~FastADocument() {
    input->close();
    delete input;
}

std::string FastADocument::getNextSequence() {
    if (input->is_open()) {
        char c;
        std::string line;
        while ((c = input->peek()) != EOF) {
            if (c == '>') {
                getline(*input, line);
            }
            getline(*input, line);
        }
    }

    return NULL;
}

