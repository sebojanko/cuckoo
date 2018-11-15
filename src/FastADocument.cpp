#include "FastADocument.h"

FastADocument::FastADocument(std::string filename) : filename_(filename) {
    input_ = new std::ifstream();
    input_->open(filename);
}

FastADocument::~FastADocument() {
    input_->close();
    delete input_;
}

std::string FastADocument::GetNextSequence() {
    if (input_->is_open()) {
        char c;
        std::string line;
        while ((c = input_->peek()) != EOF) {
            if (c == '>') {
                getline(*input_, line);
            }
            getline(*input_, line);
        }
    }

    return NULL;
}

