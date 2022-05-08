/**
 * @file jaro.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute Jaro distance [<a href="https://en.wikipedia.org/wiki/Jaro-Winkler_distance">Wikipedia link</a>]
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_JARO_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_JARO_HPP_INCLUDED

#include <math.h>
#include <algorithm>
#include <string>
#include <vector>

#include "comparator.h"

using namespace std;

namespace stringcompare {

    /**
     * @brief Jaro distance
     * 
     */
    class Jaro : public StringComparator {
    public:

        bool similarity;

        /**
         * @brief Construct a new Jaro object.
         * 
         * @param similarity Whether or not to return a similarity score rather than a distance. Defaults to false.
         */
        explicit Jaro(bool similarity = false) :
            similarity(similarity) {}

        /**
         * @brief Raw Jaro distance.
         */
        static double jaro(const string& s, const string& t) {
            auto ssize = s.size();
            auto tsize = t.size();
            if (ssize + tsize == 0) {
                return 1.0;
            }
            int window = max(1.0, floor(max(ssize, tsize) / 2.0) - 1);

            double m = 0;
            vector<bool> found_s = vector<bool>(ssize, false);
            vector<bool> found_t = vector<bool>(tsize, false);

            for (size_t i = 0; i < ssize; i++) {
                for (size_t j = 0; j < tsize; j++) {
                    if (!found_t[j] && (s[i] == t[j]) && (abs(int(i) - int(j)) < window)) {
                        m += 1;
                        found_s[i] = true;
                        found_t[j] = true;
                        break;
                    }
                }
            }

            if (m == 0) {
                return 0.0;
            }

            double transpositions = 0;
            int j = 0;
            for (size_t i = 0; i < ssize; i++) {
                if (found_s[i]) {
                    while (!found_t[j]) {
                        j += 1;
                    }
                    if (s[i] != t[j]) {
                        transpositions += 1;
                    }
                    j += 1;
                }
            }

            return (m / ssize + m / tsize + (m - transpositions / 2.0) / m) / 3.0;
        }

        double compare(const string& s, const string& t) const {
            if (this->similarity == true) {
                return jaro(s, t);
            }
            else {
                return 1.0 - jaro(s, t);
            }
        }

    };

}

#endif // STRINGCOMPARE_DISTANCE_JARO_HPP_INCLUDED