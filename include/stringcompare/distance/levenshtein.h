/**
 * @file levenshtein.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute Levenshtein distance [<a href="https://en.wikipedia.org/wiki/Levenshtein_distance">Wikipedia link</a>]
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_LEVENSHTEIN_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_LEVENSHTEIN_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "comparator.h"

using namespace std;

namespace stringcompare {

    /**
     * @brief Levenshtein distance
     * 
     * This is the minimal number number of deletions, insertions, and substitutions needed to transform one string into the other.
     */
    class Levenshtein : public StringComparator {
    public:

        bool normalize;
        bool similarity;
        int dmat_size;
        vector<int> dmat;

        /**
         * @brief Construct a new Levenshtein object.
         * 
         * By default, the Levenshtein distance `dist` is normalized to `2 * dist / (len + dist)`.
         * 
         * For two strings \f$ s \f$ and \f$ t \f$, with (unnormalized) Damerau-Levenshtein distance \f$ \texttt{dist} \f$ 
         *  (minimal number of deletions, insertions, and substitutions needed to transform one string into the other),
         *  the similarity score is defined as \f$ \texttt{sim} =  \s\+\t\ - \texttt{dist} \f$.
         * 
         * The normalized similarity score is defined as 1 minus the normalized distance.
         * 
         * @param normalize Whether to normalize the distance/similarity to be between 0 and 1. Defaults to true.
         * @param similarity Whether to return a similarity score rather than a distance. Defaults to false.
         * @param dmat_size Default starting string buffer size. If the maximum string length `s_max` is known in advance, 
         * this can be set to `s_max + 1` to improve efficiency.
         */

        Levenshtein(bool normalize = true, bool similarity = false, int dmat_size = 100) :
            normalize(normalize),
            similarity(similarity),
            dmat_size(dmat_size),
            dmat(vector<int>(dmat_size)) {}

        /**
         * @brief Raw Levenshtein distance
         */
        int levenshtein(const string& s, const string& t) {
            int m = s.size();
            int n = t.size();

            dmat.reserve(m + 1);

            for (int i = 0; i <= m; i++) {
                dmat[i] = i;
            }

            int p = m;
            int temp;
            for (int j = 1; j <= n; j++) {
                temp = j - 1;
                p = j;
                for (int i = 1; i <= m; i++) {
                    p = min({ p + 1, dmat[i] + 1, temp + (s[i - 1] != t[j - 1]) });
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

            double dist = levenshtein(s, t);

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

#endif // STRINGCOMPARE_DISTANCE_LEVENSHTEIN_HPP_INCLUDED
