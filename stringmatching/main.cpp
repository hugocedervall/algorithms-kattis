/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-05
 * @PROBLEM: stringmatching
 *      The problem is to find indicies of a pattern in a string
 *      in linear time. This is solved with a prefix function and
 *      Knuth–Morris–Pratt algorithm.
 * @COMPLEXITIES:
 *      @TIME: O(n + m), where n = length of text, m = length of pattern
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/**
 * For every position of the @param s, computes the longest proper prefix
 * that is also the suffix at the current position in the string.
 *
 * @param s input string
 * @return longest proper prefix that is also the suffix at the position
 * in the returned array.
 */
vector<int> prefix_function(string s) {
    vector<int> pi(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}


/**
 * Implementation of Knuth Morris Pratt algorithm to find
 * positions of patterns in a text.
 *
 * @param text used to find the @param pattern in
 * @param pattern the pattern to find in @param text
 * @return Indicies in @param text. where @param pattern is present
 * in @param text at the index.
 */
vector<int> find_pattern(string &text, string &pattern) {
    vector<int> res;
    vector<int> pi = prefix_function(pattern);
    // index in text and pattern
    int i = 0, j = 0;
    while (i < text.size()) {
        // If same starting pattern
        if (text[i] == pattern[j])
            i++, j++;
        // If full pattern found
        if (j == pattern.size()) {
            res.push_back(i - j);
            j = pi[j - 1];
        } else if (i < text.size() && pattern[j] != text[i]) {
            if (j != 0)
                j = pi[j - 1];
            else
                i++;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string pattern, text;
    while (getline(cin, pattern) && getline(cin, text)) {
        auto res = find_pattern(text, pattern);
        for (auto &r : res) cout << r << ' ';
        cout << '\n';
    }
    cout << flush;

    return 0;
}