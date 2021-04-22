/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-22
 * @PROBLEM: satisfiability
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

vector<string> tokenizer(string s) {
    stringstream ss(s);
    string word;
    vector<string> res;
    while (ss >> word)
        if (word != "v")
            res.push_back(word);
    return res;
}

vector<int> numberToBits(int x, int n) {
    vector<int> res(n, 0);
    for (int i = 0; i < n; ++i) {
        res[i] = (x & 1 ? 1 : -1);
        x >>= 1;
    }
    return res;
}

bool solution(vector<vector<int>> constraints, int n) {
    int nrPermutations = pow(2, n);
    vector<vector<int>> permutations(nrPermutations);
    for (int i = 0; i < nrPermutations; ++i)
        permutations[i] = numberToBits(i, n);

    // See if any permutation fufill all constrains
    for (auto &p : permutations) {
        bool satisfiable = true;
        for (auto &c : constraints) {
            bool constraintSatisfiable = false;
            bool onlyZeros = true;
            for (int i = 0; i < n; ++i) {
                if (c[i] != 0) onlyZeros = false;
                if (p[i] == c[i])
                    constraintSatisfiable = true;
            }
            // Check if all 0's
            if (!constraintSatisfiable && !onlyZeros) {
                satisfiable = false;
                break;
            }
        }
        if (satisfiable) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int nrTest, n, m;
    cin >> nrTest;

    string line;
    while (nrTest--) {
        cin >> n >> m;
        getline(cin, line);
        vector<vector<int>> constraints;
        for (int i = 0; i < m; ++i) {
            getline(cin, line);
            vector<string> elems = tokenizer(line);
            vector<int> constraint(n, 0);
            vector<bool> setTo0(n, false);
            bool addConstraint = true;

            for (auto &elem : elems) {
                int value = 1;
                if (elem[0] == '~')
                    value = -1;
                // Read which X this is
                int var = stoi(elem.substr(elem.find('X') + 1));

                // If many constraints on same variable
                if (constraint[var - 1] != 0 && constraint[var - 1] != value) {
                    addConstraint = false;
                } else
                    constraint[var - 1] = value;
            }
            if (addConstraint)
                constraints.push_back(constraint);
        }
        bool res = solution(constraints, n);
        cout << (res ? "satisfiable" : "unsatisfiable") << '\n';
    }
    cout << flush;

    return 0;
}