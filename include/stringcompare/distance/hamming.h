/**
 * @file hamming.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute the Hamming distance[<a href="https://en.wikipedia.org/wiki/Hamming_distance">Wikipedia link</a>]
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_HAMMING_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_HAMMING_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "comparator.h"

using namespace std;

namespace stringcompare {

    /**
     * @brief Hamming distance between two strings.
     * 
     * The Hamming distance is the number of sequence positions where two strings are unequal.
     */
    class Hamming : public StringComparator {
    public:

        bool normalize;
        bool similarity;

        /**
         * @brief Construct a new Hamming object.
         * 
         * By default, the Hamming distance `dist` (the number of sequence positions where two strings are unequal) is normalized to `dist/len`, where `len` is the length of the longest string.
         * 
         * The (unormalized) similarity score is defined as the length of the longest string minus the Hamming distance.
         * 
         * The normalized similarity score is 1 minus the normalized distance.
         * 
         * @param normalize Whether to normalize the distance/similarity to be between 0 and 1. Defaults to true.
         * @param similarity Whether to return a similarity score rather than a distance. Defaults to false..
         */
        Hamming(bool normalize = true, bool similarity = false) :
            normalize(normalize),
            similarity(similarity) {}

        /**
         * @brief Raw Hamming distance.
         */
        static int hamming(const string& s, const string& t) {
            int m = s.size();
            int n = t.size();
            int min_length = min(m, n);

            int distance = 0;
            for (int i = 0; i < min_length; i++) {
                distance += (s[i] != t[i]);
            }
            distance += max(m, n) - min_length;

            return distance;
        }

        double compare(const string& s, const string& t) {
            double len = max(s.size(), t.size());

            if (len == 0) {
                return similarity;
            }

            double result = hamming(s, t);

            if (similarity) {
                result = len - result;
            }
            if (normalize) {
                result = result / len;
            }

            return result;
        }

    };

}

#endif // STRINGCOMPARE_DISTANCE_HAMMING_HPP_INCLUDED