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

    class Hamming : public StringComparator {
    public:

        bool normalize;
        bool similarity;

        Hamming(bool normalize = true, bool similarity = false) :
            normalize(normalize),
            similarity(similarity) {}

        int hamming(const string& s, const string& t) {
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