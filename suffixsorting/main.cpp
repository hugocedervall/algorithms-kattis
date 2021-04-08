/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-06
 * @PROBLEM: suffixsorting
 *      The problem is to construct all the suffixes of a given string
 *      and sort them in lexographic order. This is solved with iterating through
 *      n-grams (n=2,4,8.. n<2*len(string)) of suffixes and performing radix sort.
 * @COMPLEXITIES:
 *      TIME: O(n*log(n)), n = len(string). See motivation above class SuffixArray.
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Only use first half of ASCII
static int ALPHABET_SIZE = 128;

/**
 * Implementation of sorted suffix array. This is done through
 * radix sort of n-grams. The time complexity for radix sort is O(n) and
 * the time complexity to iterate through every n-gram is log(n), therefore
 * the total time complexity is O(n*log(n)).
 */
class SuffixArray {
private:
    vector<int> sorting;

    // Holds information about suffix
    struct suffix {
        int origIndex, rank[2];
    };

    /**
     * Sorts n-grams based on given rank.
     *
     * @param suffixes All suffixes with updated ranks by the current n-gram
     * @param res in order to avoid copying @param suffixes, this is used to put our
     * results in, which can later be used to replace @param suffixes from the caller.
     * @param index which rank of the suffixes that should be used to compare, either 0 or 1.
     * @param indicies the original index of suffixes mapped to their current position in @param suffixes
     */
    static void countSort(vector<suffix> &suffixes, vector<suffix> &res, int index, vector<int> &indicies) {
        int n = suffixes.size();
        // Must be able to represent at least all characters
        vector<int> cnt(max(ALPHABET_SIZE, n), 0), p(n, 0);
        for (int i = 0; i < n; ++i)
            cnt[suffixes[i].rank[index]]++;
        for (int i = 1; i < max(ALPHABET_SIZE, n); ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            p[--cnt[suffixes[i].rank[index]]] = suffixes[i].origIndex;

        // Update results with new sort, and indicies with new indexes
        for (int i = 0; i < n; ++i) {
            res[i] = suffixes[indicies[p[i]]];
            indicies[p[i]] = i;
        }
    }

    /**
     * Divides the data into two buckets, and performs count sort on each
     * of the buckets individually.
     *
     * @param suffixes All suffixes with updated ranks by the current n-gram
     * @param indicies the original index of suffixes mapped to their current position in @param suffixes
     */
    static void radixSort(vector<suffix> &suffixes, vector<int> &indicies) {
        // To avoid copying suffixes inside countSort, use res variable. This is purely for
        // optimization. From a understanding perspective, this variable is not great.
        vector<suffix> res(suffixes.size());
        // first sort by second rank, then first. This will result in correct sorting.
        countSort(suffixes, res, 1, indicies);
        suffixes = res;
        countSort(suffixes, res, 0, indicies);
        suffixes = res;
    }

    /**
     * Builds a suffix array from the given string. This is done
     * by dividing the suffixes into n-grams, where n = 2, 4, 8, ...,
     * n < 2*len(s). These n-grams are iteratively sorted with radix sort.
     *
     * @param s string to create suffix array from
     * @return suffix array
     */
    static vector<int> buildSuffixArray(const string &s) {
        int n = s.size();
        char firstChar = '\001';
        // Store all suffixes of string
        vector<suffix> suffixes(n);
        // Keep track of new indexes for suffixes
        vector<int> indicies(n, 0);

        // Crete initial index and initial ranks for first two characters
        for (int i = 0; i < n; ++i) {
            suffixes[i].origIndex = i;
            indicies[i] = i;
            suffixes[i].rank[0] = s[i] - firstChar;
            suffixes[i].rank[1] = ((i + 1) < n) ? s[i + 1] - firstChar : 0;
        }

        // Sort based on first two chars
        radixSort(suffixes, indicies);

        // Now we want to sort according to n-gram, where n = [4, 8, ...] and n < 2*len(s)
        for (int j = 4; j < 2 * n; j *= 2) {
            // Give rank and index to first suffix
            int rank = 0, prevRank = suffixes[0].rank[0];
            suffixes[0].rank[0] = 0;
            indicies[suffixes[0].origIndex] = 0;

            // Give first rank and index to rest of suffixes
            for (int i = 1; i < n; ++i) {
                // If same ranks as previous, give same new rank
                int newRank;
                if (suffixes[i].rank[0] == prevRank &&
                    suffixes[i].rank[1] == suffixes[i - 1].rank[1])
                    newRank = rank;
                    // If bigger ranks, increase new rank
                else
                    newRank = ++rank;

                prevRank = suffixes[i].rank[0];
                suffixes[i].rank[0] = newRank;
                indicies[suffixes[i].origIndex] = i;
            }

            // Give second rank to suffixes
            for (int i = 0; i < n; ++i) {
                // Second half of suffix starts at current index + j/2
                int nextSuffixIndex = suffixes[i].origIndex + j / 2;
                if (nextSuffixIndex < n)
                    // We know the second half of current suffix already has a rank
                    suffixes[i].rank[1] = suffixes[indicies[nextSuffixIndex]].rank[0];
                else suffixes[i].rank[1] = 0;
            }

            // Sort suffixes based on new ranks
            radixSort(suffixes, indicies);
        }
        vector<int> res(n);
        for (int i = 0; i < n; ++i)
            res[i] = suffixes[i].origIndex;

        return res;
    }

    /**
     * Wraps @fn buildSuffixArray and adds a special character
     * at the end of the string.
     *
     * @param s string to create suffix array from
     * @return suffix array
     */
    static vector<int> createSuffixArray(string s) {
        // Add unique character that is lexicographically smaller than any other character in s
        s += '\002';
        vector<int> suffixArray = buildSuffixArray(s);
        // Remove added char (guaranteed to be first)
        suffixArray.erase(suffixArray.begin());
        return suffixArray;
    }

public:
    explicit SuffixArray(const string &s) {
        this->sorting = createSuffixArray(s);
    }

    int getSuffix(const int i) {
        return this->sorting[i];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    int nr, q;
    while (getline(cin, line)) {
        cin >> nr;
        auto sortedSuffix = SuffixArray(line);

        // handle queries
        for (int i = 0; i < nr; ++i) {
            cin >> q;
            cout << sortedSuffix.getSuffix(q) << " ";
        }
        cout << '\n';

        // read newline (when mixing cin and getline)
        getline(cin, line);
    }
    cout << flush;

    return 0;
}
