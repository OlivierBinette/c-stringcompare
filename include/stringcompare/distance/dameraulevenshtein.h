/**
 * @file dameraulevenshtein.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute the Damerau-Levenshtein distance [<a href="https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance">Wikipedia link</a>].
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_DAMERAULEVENSHTEIN_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_DAMERAULEVENSHTEIN_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "comparator.h"

using namespace std;

namespace stringcompare {

    template<class T>
    using Mat = vector<vector<T>>;

    /**
     * @brief Compute the Damerau-Levenshtein distance.
     * 
     * This is the number of deletions, insertions, substitutions and transpositions needed to transform one string into the other.
     * 
     */
    class DamerauLevenshtein : public StringComparator {
    public:

        bool normalize;
        bool similarity;
        int dmat_size;
        Mat<int> dmat;

        /**
         * @brief Construct a new DamerauLevenshtein object.
         * 
         * By default, the Damerau-Levenshtein distance `dist` is normalized to `2 * dist / (len + dist)`.
         * 
         * For two strings \f$ s \f$ and \f$ t \f$, with (unnormalized) Damerau-Levenshtein distance \f$ \texttt{dist} \f$ 
         *  (minimal number of deletions, insertions, substitutions and transpositions needed to transform one string into the other),
         *  the similarity score is defined as \f$ \texttt{sim} =  \s\+\t\ - \texttt{dist} \f$.
         * 
         * The normalized similarity score is defined as 1 minus the normalized distance.
         * 
         * @param normalize Whether to normalize the distance/similarity to be between 0 and 1. Defaults to true.
         * @param similarity Whether to return a similarity score rather than a distance. Defaults to false.
         * @param dmat_size Default starting string buffer size. If the maximum string length `s_max` is known in advance, 
         * this can be set to `s_max + 1` to improve efficiency.
         */
        DamerauLevenshtein(bool normalize = true, bool similarity = false, int dmat_size = 100) :
            normalize(normalize),
            similarity(similarity),
            dmat_size(dmat_size),
            dmat(Mat<int>(3, vector<int>(dmat_size))) {}


        /**
         * @brief raw Damerau-Levenshtein distance.
         */
        int dameraulevenshtein(const string& s, const string& t) {
            int m = s.size();
            int n = t.size();

            dmat[0].reserve(m+1);
            dmat[1].reserve(m+1);
            dmat[2].reserve(m+1);

            for (int i = 0; i < dmat_size; i++) {
                dmat[0][i] = i;
            }

            int cost;
            for (int j = 1; j <= n; j++) {
                dmat[(j - 1) % 3][0] = j - 1;
                dmat[j % 3][0] = j;
                for (int i = 1; i <= m; i++) {
                    cost = 0;
                    if (s[i - 1] != t[j - 1]) {
                        cost = 1;
                    }
                    dmat[j % 3][i] = min({ dmat[j % 3][i - 1] + 1, dmat[(j - 1) % 3][i] +
                                            1, dmat[(j - 1) % 3][i - 1] + cost });
                    if ((i > 1) & (j > 1) & (s[i - 1] == t[j - 2]) & (s[i - 2] == t[j - 1])) {
                        dmat[j % 3][i] = std::min({ dmat[j % 3][i], dmat[(j - 2) % 3][i - 2] + 1 });
                    }
                }
            }

            return dmat[n % 3][m];
        }

        double compare(const string& s, const string& t) {
            int len = s.size() + t.size();
            if (len == 0) {
                return similarity;
            }

            double dist = dameraulevenshtein(s, t);

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

#endif // STRINGCOMPARE_DISTANCE_DAMERAULEVENSHTEIN_HPP_INCLUDED