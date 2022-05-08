/**
 * @file tokenizer.h
 * @author Olivier Binette (https://olivierbinette.ca)
 * @brief Tokenize strings into token multisets.
 * @date 2022-04-24
 * 
 */

#ifndef STRINGCOMPARE_PREPROCESSING_TOKENIZER_HPP_INCLUDED
#define STRINGCOMPARE_PREPROCESSING_TOKENIZER_HPP_INCLUDED

#include <vector>
#include <sstream>

#include "counter.h"

using namespace std;

namespace stringcompare {

    /**
     * @brief String tokenizer base class.
     * 
     */
    class Tokenizer {
    public:

        StringCounter tokenize(const string& sentence) const {
            StringCounter result;
            return result;
        }

        StringCounter operator()(const string& sentence) const {
            return this->tokenize(sentence);
        }

        vector<StringCounter> batchTokenize(const vector<string>& sentences) const {
            vector<StringCounter> result(sentences.size());
            for (size_t i = 0; i < sentences.size(); i++) {
                result[i] = this->tokenize(sentences[i]);
            }

            return result;
        }

    };

    /**
     * @brief Tokenize strings by a given delimiter.
     */
    class DelimTokenizer : public Tokenizer {
    public:

        string delim;

        explicit DelimTokenizer(const string& delim) :delim(delim) {
            if (this->delim.size() == 0) {
                throw runtime_error("Delimiter is empty.");
            }
        }

        StringCounter tokenize(const string& sentence) const {
            StringCounter result;

            if (sentence.size() == 0) {
                return result;
            }

            size_t k = this->delim.size();
            size_t pos = 0;
            size_t match = 0;

            while ((match = sentence.find(this->delim, pos)) != string::npos) {
                if (match != pos) {
                    result.insert(sentence.substr(pos, match - pos));
                }
                pos = match + k;
            }
            if (pos < sentence.size()) {
                result.insert(sentence.substr(pos));
            }

            return result;
        }
    };

    /**
     * @brief Tokenize strings by whitespace.
     */
    class WhitespaceTokenizer : public DelimTokenizer {
    public:
        WhitespaceTokenizer() : DelimTokenizer(" ") {}
    };

    /**
     * @brief Tokenize strings by sequential n-grams.
     */
    class NGramTokenizer : public Tokenizer {
    public:

        int n;

        explicit NGramTokenizer(int n) {
            this->n = n;
        }

        StringCounter tokenize(const string& sentence) const {
            StringCounter result;

            if (this->n <= 0) {
                return result;
            }

            for (size_t i = 0; i < sentence.size() - this->n; i++) {
                result.insert(sentence.substr(i, this->n));
            }

            return result;
        }
    };

}

#endif // STRINGCOMPARE_PREPROCESSING_TOKENIZER_HPP_INCLUDED