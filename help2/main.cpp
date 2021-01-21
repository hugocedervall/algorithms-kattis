/**
 * @PROBLEM: help!
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-21
 *
 * Comments:
 *  - Iterating through the words and replace with placeholder mappings,
 *      this is done until there are no more actions to take.
 *
 * Complexity:
 *  - O(n²) where n = #words (so max 100/16=6.25)
 *
 * Learned:
 *  - Combining cin and getline is not convenient
 */
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Splits sentence into words based on spaces
 * @return vector with words from sentence
 */
vector<string> stringSplit(string sentence) {
    vector<string> res;
    istringstream iss;

    iss.str(sentence);
    string tmpS;
    while (iss >> tmpS) {
        res.push_back(tmpS);
    }
    return res;
}

bool isPlaceHolder(const string &s) {
    return (s[0] == '<' && s[s.length() - 1] == '>');
}

/**
 * Iterating through the words and replace with placeholder mappings,
 *  this is done until there are no more actions to take.
 *
 * @return sentence without placeholders if it's possible to satisfy the constraints.
 * otherwise "-".
 */
string solution(string sentence1, string sentence2) {
    vector<string> s1Words = stringSplit(sentence1);
    vector<string> s2Words = stringSplit(sentence2);

    if (s1Words.size() != s2Words.size()) return "-";

    map<string, string> placeholderMap1;
    map<string, string> placeholderMap2;

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < s1Words.size(); ++i) {
            bool s1PlaceHolder = isPlaceHolder(s1Words[i]);
            bool s2PlaceHolder = isPlaceHolder(s2Words[i]);

            if (!s1PlaceHolder && !s2PlaceHolder) continue;

            // Replace if placehounder mapping found
            if (s1PlaceHolder && placeholderMap1.find(s1Words[i]) != placeholderMap1.end()) {
                s1Words[i] = placeholderMap1[s1Words[i]];
                changed = true;
                s1PlaceHolder = false;
            }
            if (s2PlaceHolder && placeholderMap2.find(s2Words[i]) != placeholderMap2.end()) {
                s2Words[i] = placeholderMap2[s2Words[i]];
                changed = true;
                s2PlaceHolder = false;
            }

            // Insert placeholder mapping
            if (s1PlaceHolder && !s2PlaceHolder) {
                // If already found and it is not same as other word
                if (placeholderMap1.find(s1Words[i]) == placeholderMap1.end()) {
                    placeholderMap1[s1Words[i]] = s2Words[i];
                }
                s1Words[i] = placeholderMap1[s1Words[i]];

                changed = true;
            } else if (s2PlaceHolder && !s1PlaceHolder) {
                // If already found and it is not same as other word
                if (placeholderMap2.find(s2Words[i]) == placeholderMap2.end()) {
                    placeholderMap2[s2Words[i]] = s1Words[i];
                }
                s2Words[i] = placeholderMap2[s2Words[i]];
                changed = true;
            }
        }
    } while (changed);

    // Replace placeholders pointing to placeholders with the same "random" char "x"
    string tmpStr = "x";
    for (int i = 0; i < s1Words.size(); ++i) {
        bool s1PlaceHolder = isPlaceHolder(s1Words[i]);
        bool s2PlaceHolder = isPlaceHolder(s2Words[i]);

        // unused placeholder?
        if (s1PlaceHolder && s2PlaceHolder) {
            s1Words[i] = tmpStr;
            s2Words[i] = tmpStr;
        }
    }

    // See if s1words and s2words are the same sentences
    if (equal(s1Words.begin(), s1Words.end(), s2Words.begin())) {
        string res;
        for (auto it = s1Words.begin(); it != s1Words.end(); it++) {
            res += *it;
            if (it != (s1Words.end() - 1)) {
                res += " ";
            }
        }
        return res;
    }
    return "-";
}

int main() {
    int n;
    cin >> n;

    string sent1, sent2;

    // Since std::cin leaves \n, it will be removed by this
    getline(cin, sent1);

    for (int i = 0; i < n; ++i) {
        getline(cin, sent1);
        getline(cin, sent2);

        string res = solution(sent1, sent2);
        cout << res << endl;
    }

    return 0;
}
