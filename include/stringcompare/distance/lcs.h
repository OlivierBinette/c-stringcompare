/**
 * @file lcs.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute Longest Common Substring (LCS) distance [<a href="https://en.wikipedia.org/wiki/Longest_common_substring_problem">Wikipedia link</a>]
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_LCS_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_LCS_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "comparator.h"

using namespace std;

namespace stringcompare {

    /**
     * @brief Longest Common Substring (LCS) distance.
     */
    class LCSDistance : public StringComparator {
    public:

        bool normalize;
        bool similarity;
        int dmat_size;
        vector<int> dmat;

        /**
         * @brief Construct a new LCSDistance object.
         * 
         * The LCS distance is the sum of the lengths of the string minus twice the length of their longest common substring.
         * 
         * By default, the LCS distance `dist` is normalized to `2 * dist / (len + dist)`.
         * 
         * The (unnormalized) similarity score is defined as the length of the longest common substring. 
         * 
         * The normalized similarity score is 1 minus the normalized distance.
         * 
         * @param normalize Whether to normalize the distance/similarity to be between 0 and 1. Defaults to true.
         * @param similarity Whether to return a similarity score rather than a distance. Defaults to false.
         * @param dmat_size Default starting string buffer size. If the maximum string length `s_max` is known in advance, 
         * this can be set to `s_max + 1` to improve efficiency.
         */

        LCSDistance(bool normalize = true, bool similarity = false, int dmat_size = 100) :
            normalize(normalize),
            similarity(similarity),
            dmat_size(dmat_size),
            dmat(vector<int>(dmat_size)) {}

        /**
         * @brief Length of the longest common substring.
         */
        int lcs(const string& s, const string& t) {
            int m = s.size();
            int n = t.size();

            dmat.reserve(m + 1);

            for (int i = 0; i < dmat_size; i++) {
                dmat[i] = 0;
            }

            int p = 0;
            int temp;
            for (int j = 1; j <= n; j++) {
                temp = 0;
                p = 0;
                for (int i = 1; i <= m; i++) {
                    if (s[i - 1] != t[j - 1]) {
                        p = max({ dmat[i], p });
                    }
                    else {
                        p = temp + 1;
                    }
                    temp = dmat[i];
                    dmat[i] = p;
                }
            }

            return p;
        }

        double compare(const string& s, const string& t) {
            double len = s.size() + t.size();
            if (len == 0) {
                return similarity;
            }

            double dist = len - 2.0 * lcs(s, t);
            if (similarity) {
                double sim = (len - dist) / 2.0;
                if (normalize) {
                    sim = sim / (len - sim);
                }
                return sim;
            }
            else {
                if (normalize) {
                    dist = 2 * dist / (len + dist);
                }
                return dist;
            }
        }

    };

}

#endif // STRINGCOMPARE_DISTANCE_LCS_HPP_INCLUDED