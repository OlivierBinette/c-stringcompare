#ifndef STRINGCOMPARE_DISTANCE_COMPARATOR_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_COMPARATOR_HPP_INCLUDED

#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

namespace stringcompare {

    template<class T>
    using Mat = vector<vector<T>>;

    template<class dtype>
    class Comparator {
    public:
        virtual double compare(const dtype& s, const dtype& t) = 0;

        double operator()(const dtype& s, const dtype& t) {
            return compare(s, t);
        }

        vector<double> elementwise(const vector<dtype>& l1, const vector<dtype>& l2) {

            if (l1.size() != l2.size()) {
                throw runtime_error("Lists should be of the same size.");
            }

            vector<double> result(l1.size());
            for (size_t i = 0; i < l1.size(); i++) {
                result[i] = this->compare(l1[i], l2[i]);
            }

            return result;
        }

        Mat<double> pairwise(const vector<dtype>& l1, const vector<dtype>& l2) {
            Mat<double> result;
            result.reserve(l1.size());
            for (size_t i = 0; i < l1.size(); i++) {
                result[i].reserve(l2.size());
                for (size_t j = 0; j < l2.size(); j++) {
                    result[i][j] = this->compare(l1[i], l2[j]);
                }
            }

            return result;
        }

    };

    class StringComparator : public Comparator<string> {};

    class NumericComparator : public Comparator<double> {};

}

#endif // STRINGCOMPARE_DISTANCE_COMPARATOR_HPP_INCLUDED