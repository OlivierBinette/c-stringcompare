#ifndef STRINGCOMPARE_DISTANCE_JACCARD_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_JACCARD_HPP_INCLUDED

#include <string>
#include <vector>

#include "comparator.h"
#include "../preprocessing/tokenizer.h"

using namespace std;

namespace stringcompare {

    class Jaccard : public StringComparator {
    public:

        Tokenizer tokenizer;
        bool normalize;
        bool similarity;

        Jaccard(Tokenizer tokenizer, bool normalize = true, bool similarity = false) :
            tokenizer(tokenizer),
            normalize(normalize),
            similarity(similarity) {}

        double compare(const string& s, const string& t) {
            return tokenizer(s).intersectionCount(tokenizer(t)) / tokenizer(s).unionCount(tokenizer(t));
        }

    };

}

#endif // STRINGCOMPARE_DISTANCE_JACCARD_HPP_INCLUDED