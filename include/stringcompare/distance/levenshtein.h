#ifndef STRINGCOMPARE_DISTANCE_LEVENSHTEIN_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_LEVENSHTEIN_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "comparator.h"

using namespace std;

namespace stringcompare {

    class Levenshtein : public StringComparator {
    public:

        bool normalize;
        bool similarity;
        int dmat_size;
        bool check_bounds;
        vector<int> dmat;

        Levenshtein(bool normalize = true, bool similarity = false, int dmat_size = 100, bool check_bounds = true) :
            normalize(normalize),
            similarity(similarity),
            dmat_size(dmat_size),
            check_bounds(check_bounds),
            dmat(vector<int>(dmat_size)) {}

        int levenshtein(const string& s, const string& t) {
            int m = s.size();
            int n = t.size();

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
            if (check_bounds) {
                dmat.reserve(s.size() + 1);
            }

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