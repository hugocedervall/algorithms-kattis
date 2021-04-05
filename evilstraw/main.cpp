/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-05
 * @PROBLEM: evilstraw
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int solution(string s) {
    int swaps = 0;
    int l = 0, r = s.size() - 1;

    while (l <= r) {
        // If the left and right char are not the same
        if (s[l] != s[r]) {
            // Find char which matches left or right, with the
            // shortest swaps
            int ll = l + 1, rr = r - 1;
            bool found = false;
            while (!found && ll < r && rr > l) {
                // Swap ll to l
                if (s[ll] == s[r]) {
                    swaps += (ll - l);
                    // swap all between l and ll one step to right
                    for (int i = ll; i > l; --i)
                        s[i] = s[i - 1];
                    s[l] = s[r];
                    found = true;
                }
                // Swap rr to r
                else if (s[rr] == s[l]) {
                    swaps += (r - rr);
                    // swap all between r and rr one step to left
                    for (int i = rr; i < r; ++i)
                        s[i] = s[i + 1];
                    s[r] = s[l];
                    found = true;
                }
                ll++, rr--;
            }
            // Could not find any to swap
            if (!found) return -1;
        }
        l++, r--;
    }
    return swaps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        auto res = solution(s);
        cout << (res >= 0 ? to_string(res) : "Impossible") << '\n';
    }
    cout << flush;

    return 0;
}