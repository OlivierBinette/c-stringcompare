/**
 * @file characterdifference.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Compute character overlap between strings.
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_DISTANCE_CHARACTERDIFFERENCE_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_CHARACTERDIFFERENCE_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "comparator.h"

using namespace std;

namespace stringcompare {

    template<class T>
    using Mat = vector<vector<T>>;
    
    /**
     * @brief Compute character overlap between strings.
     * 
     */
    class CharacterDifference : public StringComparator {
    public:

        bool normalize;
        bool similarity;

        /**
         * @brief Construct a new CharacterDifference object.
         * 
         * Calls to operator()() and compare() return the comparison value.
         * 
         * Given two strings, let \f$ A \f$ and \f$ B \f$ be their character multisets. Then the CharacterDifference distance
         * between the two strings is defined as \f$ d = |A| + |B| - 2|A \cap B| \f$.
         * 
         * By default, the distance is normalized to \f$ 2d / (|A| + |B| + d) \f$.

         * The similarity score is defined as \f$ |A \cap B| \f$ and its normalization is 
         * \f[
         *     \frac{|A \cap B|}{|A| + |B| - |A \cap B|}.
         * \f]
         * 
         * @param normalize Whether to normalize the difference value to be between 0 and 1. Defaults to true.
         * @param similarity Whether to return a similarity score rather than a distance. Defaults to false.
         */
        CharacterDifference(bool normalize = true, bool similarity = false) :
            normalize(normalize),
            similarity(similarity) {}

        /**
         * @brief Number of characters in common between two strings
         * 
         * @param s string to compare from.
         * @param t string to compare to.
         * @return int Number of characters in common.
         */
        static int commoncharacters(const string& s, const string& t) {
            string s1 = s;
            string s2 = t;

            sort(begin(s1), end(s1));
            sort(begin(s2), end(s2));

            std::string intersection;
            std::set_intersection(begin(s1), end(s1), begin(s2), end(s2),
                back_inserter(intersection));
            return (int)intersection.size();
        }

        double compare(const string& s, const string& t) {
            int len = s.size() + t.size();

            if (len == 0) {
                return similarity;
            }

            double dist = len - 2 * commoncharacters(s, t);

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

#endif // STRINGCOMPARE_DISTANCE_CHARACTERDIFFERENCE_HPP_INCLUDED