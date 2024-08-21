#ifndef __SIMHASH_H__
#define __SIMHASH_H__

#include "../Simhash/Simhasher.hpp"

// #include "FileProcessor.h"
#include <string>
using namespace simhash;

using std::string;

class CompareU64 {
public:
    bool operator()(const std::pair<uint64_t, string> &a,
                    const std::pair<uint64_t, string> &b) const {
        return !simhash::Simhasher::isEqual(a.first, b.first);
    }

private:
    // simhash::Simhasher _simhasher;
};

#endif
