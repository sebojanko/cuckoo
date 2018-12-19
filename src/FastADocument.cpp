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
    std::string ret("");
    if (input_->is_open()) {
        char c;
        std::string line;
        while ((c = input_->peek()) != EOF) {
            if (c == '>') {
                std::string comment;
                getline(*input_, comment);
            } else {
                while (input_->get(c)) {
                    if (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == '>') {
                        if (c == '>') {
                            input_->unget();
                            break;
                        }
                        ret += c;
                    }
                }
            }
        }
    }
    return ret;
}

