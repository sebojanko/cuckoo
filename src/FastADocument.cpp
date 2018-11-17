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
        bool flag = false;
        while ((c = input_->peek()) != EOF) {
            if (c == '>') {
                if (flag) {
                    break;
                }

                std::string comment;
                getline(*input_, comment);
                flag = true;
            } else {
                getline(*input_, line);
                ret += line;
            }
        }
    }
    return ret;
}

