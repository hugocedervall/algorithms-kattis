/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-26
 * @PROBLEM: aliens
*/


#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Subtract this from all chars
static char CHANGE_CHAR = 0;

/**
 * Implementation of sorted suffix array. This is done through
 * radix sort of n-grams. The time complexity for radix sort is O(n) and
 * the time complexity to iterate through every n-gram is log(n), therefore
 * the total time complexity is O(n*log(n)).
 */
class SuffixArray {
private:
    string s;
    vector<int> suffixArray;
    vector<int> lcp;

    // Holds information about suffix
    struct suffix {
        int origIndex, rank[2];
    };

    static int cmp(struct suffix a, struct suffix b) {
        return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) :
               (a.rank[0] < b.rank[0] ? 1 : 0);
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
        sort(suffixes.begin(), suffixes.end(), cmp);
        // For some reason it isn't working with radix sort atm
        //radixSort(suffixes, indicies);

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
            sort(suffixes.begin(), suffixes.end(), cmp);
            // For some reason it isn't working with radix sort atm
            //radixSort(suffixes, indicies);
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

    /**
     * May be called after an suffix array has already been built
     * @return
     */
    vector<int> buildLcp(const string &s) {
        int n = this->suffixArray.size();
        vector<int> lcpArray(n, 0);
        vector<int> invSuffix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            invSuffix[this->suffixArray[i]] = i;
        // Prev len of lcpArray
        int k = 0;

        for (int i = 0; i < n; ++i) {
            // Last index is undefined, always 0
            if (invSuffix[i] == 0) {
                k = 0;
                continue;
            }

            // Look at previous suffix
            int j = this->suffixArray[invSuffix[i] - 1];

            // Count length of shared prefix of suffixes
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcpArray[invSuffix[i]] = k;

            if (k > 0) k--;
        }
        return lcpArray;
    }

    /**
     *
     * @param x The minimum length of prefix that is searched for
     * @param nrWords Amont of words in input
     * @param indexToWord Mapping from index in the total string to the initial word index
     * @param res Prefixes of at least length @param x, which are present in more than half of initial words
     * @param stopEarly If true, algorithm will only tell if there is an answer, not the actual solution. Used to
     * optimize the solution.
     * @return If there is an solution or not
     */
    bool
    findLcp(const int &x, const int &nrWords, map<string, int> &res, int minLen, bool earlyStop) {
        //set<string> res;
        int n = this->suffixArray.size();
        // Amount of times found, its enough with N/2
        int count;
        // Mark which words have the

        for (int i = 1; i < n; ++i) {
            // If longer or same as given searched length
            if (this->lcp[i] >= x) {
                count = 1;

                // Search for other suffixes of same length
                int ii = i;
                while (ii < n && this->lcp[ii] >= x) {
                    // if new suffix
                    /*if (indexToWord[this->suffixArray[ii]] != indexToWord[this->suffixArray[ii] + x - 1])
                        break;*/
                    // Found matching prefix from other initial word
                    count++;
                    ii++;
                }

                // One solution found, must continue though, in order to find all prefixes of length x
                if (count >= minLen) {
                    string r = "";
                    for (int j = 0; j < x; ++j) {
                        char a = (s[this->suffixArray[i] + j]);
                        r += (a + CHANGE_CHAR);
                    }
                    // Amount of found with pattern
                    res[r] = max(count, res[r]);
                }
                // All have already been checked
                i = ii - 1;
            }
        }
        //return res;
        return !res.empty();
    }

public:
    explicit SuffixArray(const string &s) {
        this->s = s;
        this->suffixArray = createSuffixArray(s);
        // Must be built after suffix array
        this->lcp = buildLcp(s);
    }


    tuple<int, int>
    getLongestCommonPrefix(const int &longestWord, int minLen, string s) {

        // Binary search through all possible lengths
        // longest string

        int mid, low = 1, high = longestWord;
        int solution = -1;
        int resmaxIndex = 0;
        while (low <= high) {
            mid = (high + low) / 2;
            map<string, int> counts;

            // See if there is any solution
            auto foundSolution = findLcp(mid, 1, counts, minLen, true);
            if (foundSolution && mid > solution) {
                solution = mid;
                low = mid + 1;

                int maxIndex = 0;
                for (auto &r:counts) {
                    int lastPos = s.rfind(get<0>(r));
                    if (lastPos > maxIndex) maxIndex = lastPos;
                }
                resmaxIndex = maxIndex;
            } else
                high = mid - 1;
        }

        return {solution, resmaxIndex};
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string line;

    while (cin >> n && n != 0) {
        // since cin was used
        getline(cin, line);
        string s;
        getline(cin, s);

        /*string s = "";
        for (auto &c : line) {
            s.push_back(c - CHANGE_CHAR);
        }*/

        if (n == 1) {
            cout << s.size() << " " << 0 <<  '\n';
        } else {
            auto sortedSuffix = SuffixArray(s);

            auto res = sortedSuffix.getLongestCommonPrefix(s.size(), n, s);
            if (get<0>(res) > 0) {
                cout << get<0>(res) << " " << get<1>(res) << '\n';
            } else
                cout << "none\n";
        }
    }

    cout << flush;

    return 0;
}