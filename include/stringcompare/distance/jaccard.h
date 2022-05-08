/**
 * @file jaccard.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute Jaccard distance (overlap between token sets) [<a href="https://en.wikipedia.org/wiki/Jaccard_index">Wikipedia link</a>]
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_JACCARD_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_JACCARD_HPP_INCLUDED

#include <string>
#include <vector>

#include "comparator.h"
#include "../preprocessing/tokenizer.h"

using namespace std;

namespace stringcompare {

    /**
     * @brief Jaccard distance between tokenized strings.
     * 
     */
    class Jaccard : public StringComparator {
    public:

        Tokenizer tokenizer;
        bool normalize;
        bool similarity;

        /**
         * @brief Construct a new Jaccard object.
         * 
         * The Jaccard distance between token bags is 1 minus their percentage of overlap.
         * 
         * The similarity score is the percentage of overlap.
         * 
         * @param tokenizer Tokenizer object.
         * @param similarity Whether to return a similarity score rather than a distance. Defaults to false.
         */
        Jaccard(Tokenizer tokenizer, bool normalize = true, bool similarity = false) :
            tokenizer(tokenizer),
            similarity(similarity) {}

        double compare(const string& s, const string& t) {
            return tokenizer(s).intersectionCount(tokenizer(t)) / tokenizer(s).unionCount(tokenizer(t));
        }

    };

}

#endif // STRINGCOMPARE_DISTANCE_JACCARD_HPP_INCLUDED