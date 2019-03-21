#ifndef SRC_SIMPLEENCODER_H_
#define SRC_SIMPLEENCODER_H_

#include <string>

// created by David on 18/12/18

// Encodes a k-mer string into a uint64_t.
// Can encode up to 20 characters (20-mers).
// If a string of length > 20 is provided, only
// ghe first 20 characters are encoded.
// Example:
//    SimpleEncoder enc;
//    uint64_t encoded = enc.encode("CACAGT");
//    std::string decoded = enc.decode(encoded);
class SimpleEncoder {
 public:
    uint64_t Encode(const std::string& item) const;
    std::string Decode(uint64_t encoded);

    // same as encode
    uint64_t operator()(std::string item);

 private:
    size_t bits_per_char_ = 3;
};

#endif  // SRC_SIMPLEENCODER_H_
