/**
 * @file jarowinkler.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute Jaro-Winkler distance [<a href="https://en.wikipedia.org/wiki/Jaro-Winkler_distance">Wikipedia link</a>]
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_JAROWINKLER_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_JAROWINKLER_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "jaro.h"

using namespace std;

namespace stringcompare {

    /**
     * @brief Jaro-Winkler distance
     */
    class JaroWinkler : public StringComparator {
    public:

        bool similarity;

        /**
         * @brief Construct a new Jaro Winkler object
         * 
         * @param similarity Whether or not to return a similarity score rather than a distance. Defaults to false.
         */
        explicit JaroWinkler(bool similarity = false) :
            similarity(similarity) {}

        /**
         * @brief Raw Jaro-Winkler distance.
         */
        static double jarowinkler(const string& s, const string& t, double p = 0.1) {
            int ell = 0;
            for (size_t i = 0; i < min({ s.size(), t.size(), size_t(4) }); i++) {
                if (s[i] == t[i]) {
                    ell += 1;
                }
                else {
                    break;
                }
            }

            double sim = Jaro::jaro(s, t);

            return sim + ell * p * (1 - sim);
        }

        double compare(const string& s, const string& t) const {
            if (this->similarity == true) {
                return jarowinkler(s, t);
            }
            else {
                return 1.0 - jarowinkler(s, t);
            }
        }

    };

}

#endif // STRINGCOMPARE_DISTANCE_JAROWINKLER_HPP_INCLUDED