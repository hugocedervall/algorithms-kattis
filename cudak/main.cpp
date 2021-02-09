/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-09
 * @PROBLEM: cudak
*/

#include <bits/stdc++.h>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

int SMAX = 135, LMAX = 15;

// Returns length of given number
int nrLen(ll nr) {
    return int(log10(nr)) + 1;
}

ll solution(vector<vector<ll>> &dp, ll A, ll S) {
    int lenA = nrLen(A);
    // Add each individual number of A
    vector<ll> numbers(lenA);
    for (int i = 0; i < lenA; ++i) {
        numbers[i] = A % 10;
        A /= 10;
    }

    ll res = 0, sum = 0;
    // Start at end since numbers is wrong order
    for (int i = numbers.size() - 1; i >= 0; --i) {
        // Sum S x rest matrix without already counted values
        for (int j = 0; j < numbers[i]; ++j) {
            if (S - sum - j >= 0)
                res += dp[i][S - sum - j];
        }
        sum += numbers[i];
    }
    return sum == S ? res + 1 : res;
}

// Binary search to find first breaking point where solution(A)
// is increased, then we know there is a new solution
ll first(vector<vector<ll>> &dp, ll A, ll B, ll S) {
    ll right = B, left = A, mid;
    while (left != right) {
        mid = (left + right + 1) / 2;

        auto midSol = solution(dp, mid, S);
        auto leftSol = solution(dp, left, S);
        // If there is the same amount of solutions at mid
        // and low, we have not found the first nr
        if (midSol == leftSol)
            left = mid;
        else
            right = --mid;
    }
    return left + 1;
}

void fillDp(vector<vector<ll>> &dp) {
    // There is 1 possible way to get sum 0 with length 0
    dp[0][0] = 1;

    // Amount of ways to get sum s with len l is
    // the sum of in row s-1 for columns 0...l.
    for (int r = 1; r <= LMAX; ++r) {
        for (int c = 0; c <= SMAX; ++c) {
            // For all columns on row above
            for (int i = c; i >= 0 && i > (c - 10); --i) {
                dp[r][c] += dp[r - 1][i];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<ll>> dp(LMAX + 1, vector<ll>(SMAX + 1, 0));

    fillDp(dp);

    ll A, B, S;
    cin >> A >> B >> S;
    cout << solution(dp, B, S) - solution(dp, A, S) << '\n';
    cout << first(dp, A, B, S) << '\n';
    cout << flush;

    return 0;
}