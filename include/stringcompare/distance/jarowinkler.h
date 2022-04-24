#ifndef STRINGCOMPARE_DISTANCE_JAROWINKLER_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_JAROWINKLER_HPP_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "jaro.h"

using namespace std;

namespace stringcompare {

    class JaroWinkler : public StringComparator {
    public:

        bool similarity;

        explicit JaroWinkler(bool similarity = false) :
            similarity(similarity) {}

        double jarowinkler(const string& s, const string& t, double p = 0.1) const {
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