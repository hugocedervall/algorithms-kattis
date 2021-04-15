/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-15
 * @PROBLEM: Lifeforms
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Only use first half of ASCII
static int ALPHABET_SIZE = 128;

// Subtract this from all chars
static char CHANGE_CHAR = 'a' - 1;

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
        // first sort by second rank, then first. This will result in correct suffixArray.
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
    bool findLcp(const int &x, const int &nrWords, const vector<int> &indexToWord, set<string> &res, bool stopEarly) {
        //set<string> res;
        int n = this->suffixArray.size();
        // Amount of times found, its enough with N/2
        int count;
        // Mark which words have the
        vector<bool> marked(nrWords, false);

        for (int i = 1; i < n; ++i) {
            // If longer or same as given searched length
            if (this->lcp[i] >= x) {
                fill(marked.begin(), marked.end(), false);
                count = 1;
                marked[indexToWord[suffixArray[i - 1]]] = true;

                // Search for other suffixes of same length
                int ii = i;
                while (ii < n && this->lcp[ii] >= x) {
                    // if new suffix
                    if (indexToWord[this->suffixArray[ii]] != indexToWord[this->suffixArray[ii] + x - 1])
                        break;
                    // Found matching prefix from other initial word
                    if (!marked[indexToWord[this->suffixArray[ii]]]) {
                        marked[indexToWord[this->suffixArray[ii]]] = true;
                        count++;
                    }
                    ii++;
                }

                // One solution found, must continue though, in order to find all prefixes of length x
                if (count > nrWords / 2) {
                    if (stopEarly) return true;
                    string r = "";
                    for (int j = 0; j < x; ++j) {
                        char a = (s[this->suffixArray[i] + j]);
                        r += (a + CHANGE_CHAR);
                    }
                    res.insert(r);
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

    int getSuffix(const int i) {
        return this->suffixArray[i];
    }

    set<string> getLongestCommonPrefix(const int &longestWord, const int &nrWords, const vector<int> &indexToWord) {
        // Return the same string as input, but decode it back to real chars
        if (nrWords == 1) {
            string tmp = this->s;
            for (int i = 0; i < tmp.size(); ++i)
                tmp[i] += CHANGE_CHAR;
            return set<string>{tmp};
        }

        // Binary search through all possible lengths
        int mid, low = 1, high = longestWord;
        int solution = -1;
        while (low <= high) {
            mid = (high + low) / 2;
            set<string> res;
            // See if there is any solution
            auto foundSolution = findLcp(mid, nrWords, indexToWord, res, true);
            if (foundSolution && mid > solution) {
                solution = mid;
                low = mid + 1;
            } else
                high = mid - 1;
        }
        // Now get the actual results
        set<string> res = set<string>();
        // If there was any found solution
        if (solution > 0)
            findLcp(solution, nrWords, indexToWord, res, false);

        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    int nr;
    while (cin >> nr && nr != 0) {
        // read newline (when mixing cin and getline)
        getline(cin, line);
        vector<int> indexToWord;
        int longestWord = 0;
        string s = "";
        for (int i = 0; i < nr; ++i) {
            getline(cin, line);
            for (auto &c : line)
                s.push_back(c - CHANGE_CHAR);
            //s += line;

            if (line.length() > longestWord)
                longestWord = line.length();

            for (int j = 0; j < line.size(); ++j)
                indexToWord.push_back(i);

            // Add unique character between words
            if (i != nr - 1) {
                //s.push_back(200 + i);
                s.push_back(CHANGE_CHAR + 1 + i);
                indexToWord.push_back(i);
            }
        }
        auto sortedSuffix = SuffixArray(s);

        auto res = sortedSuffix.getLongestCommonPrefix(longestWord, nr, indexToWord);
        if (!res.empty())
            for (auto &r : res)
                cout << r << '\n';
        else
            cout << "?" << '\n';

        cout << '\n';

    }
    cout << flush;

    return 0;
}