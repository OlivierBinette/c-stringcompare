/**
 * @file comparator.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Base class for string comparison functions.
 * @date 2022-04-24
 *
 */

#ifndef STRINGCOMPARE_DISTANCE_COMPARATOR_HPP_INCLUDED
#define STRINGCOMPARE_DISTANCE_COMPARATOR_HPP_INCLUDED

#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

namespace stringcompare {

    template<class T>
    using Mat = vector<vector<T>>;

    /**
     * @brief Base class for comparators.
     *
     * Requires a compare() function. Implements the callable @c operator()(), and the @c elementwise() and @c pairwise() functions.
     *
     * @tparam dtype Type of objects to compare (typically `string`).
     */
    template<class dtype>
    class Comparator {
    public:

        /**
         * @brief Interface to comparison functions.
         *
         * @param s Object to compare from.
         * @param t Object to compare to.
         * @return double Comparison value.
         */
        virtual double compare(const dtype& s, const dtype& t) = 0;

        /**
         * @brief Instances are callable for simplicity.
         *
         * @param s Object to compare from.
         * @param t Object to compare to.
         * @return double Comparison value between s and t.
         */
        double operator()(const dtype& s, const dtype& t) {
            return compare(s, t);
        }

        /**
         * @brief Elementwise comparisons between vectors. The two vectors should be of the same size.
         *
         * @param l1 Vector of elements to compare from.
         * @param l2 Vector of elements to compare to.
         * @return vector<double> Vector of comparison values between coresponding elements in the lists.
         */
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

        /**
         * @brief Pairwise comparisons between the elements of two vectors.
         *
         * @param l1 Vector of elements to compare from.
         * @param l2 Vector of elements to compare to.
         * @return Mat<double> Matrix of comparison values, where element (i,j) is the comparison between the first list's ith element and the second list jth element.
         */
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

    /**
     * @brief Comparator for string elements.
     * 
     */
    class StringComparator : public Comparator<string> {};

    /**
     * @brief Comparator for numeric values.
     * 
     */
    class NumericComparator : public Comparator<double> {};

}

#endif // STRINGCOMPARE_DISTANCE_COMPARATOR_HPP_INCLUDED