/**
 * @file counter.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief (pybind11-friendly) multiset implementation.
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_PREPROCESSING_COUNTER_HPP_INCLUDED
#define STRINGCOMPARE_PREPROCESSING_COUNTER_HPP_INCLUDED

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

namespace stringcompare {

    typedef unsigned long int count_t;

    /**
     * String multiset implemented as a map from elements to their count.
     *
     * \note This is for ease of use with pybind11.
     */
    class StringCounter {
    public:
        map<string, count_t> dict;

        StringCounter() {};

        map<string, count_t> getDict() {
            return this->dict;
        }

        count_t intersectionCount(const StringCounter& other) {

            // Swap `this` and `other` for efficiency, if needed.
            count_t sum = 0;
            if (dict.size() < other.dict.size()) {
                const map<string, count_t>& a = this->dict;
                const map<string, count_t>& b = other.dict;

                for (auto it = a.begin(); it != a.end(); it++) {
                    auto search = b.find(it->first);
                    if (search != b.end()) {
                        sum += min(it->second, search->second);
                    }
                }

                return sum;
            }
            else {
                const map<string, count_t>& b = this->dict;
                const map<string, count_t>& a = other.dict;

                for (auto it = a.begin(); it != a.end(); it++) {
                    auto search = b.find(it->first);
                    if (search != b.end()) {
                        sum += min(it->second, search->second);
                    }
                }

                return sum;
            }
        }

        count_t unionCount(const StringCounter& other) {
            return this->total() + other.total() - this->intersectionCount(other);
        }

        void insert(const string& element) {
            auto it = dict.find(element);
            if (it != dict.end()) {
                it->second++;
            }
            else {
                dict.insert(pair<string, int>(element, 1));
            }
        }

        void remove(const string& element) {
            auto it = dict.find(element);
            if (it != dict.end()) {
                if (it->second <= 1) {
                    dict.erase(it);
                }
                else {
                    it->second--;
                }
            }
        }

        set<string> elements() const {
            set<string> result;
            for (auto it = dict.begin(); it != dict.end(); it++) {
                result.insert(it->first);
            }

            return result;
        }

        count_t total() const {
            int total = 0;
            for (auto it = dict.begin(); it != dict.end(); it++) {
                total += it->second;
            }

            return total;
        }

        count_t unique() const {
            return dict.size();
        }

        static StringCounter fromList(const vector<string>& vect) {
            StringCounter result;
            for (auto it = vect.begin(); it != vect.end(); it++) {
                result.insert(*it);
            }

            return result;
        }
    };

}

#endif // STRINGCOMPARE_PREPROCESSING_COUNTER_HPP_INCLUDED