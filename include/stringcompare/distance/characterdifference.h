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

    class CharacterDifference : public StringComparator {
    public:

        bool normalize;
        bool similarity;

        CharacterDifference(bool normalize = true, bool similarity = false) :
            normalize(normalize),
            similarity(similarity) {}

        int commoncharacters(const string& s, const string& t) {
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