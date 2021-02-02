/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-02
 * @PROBLEM: perfectpowers
*/

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 * long as input to handle abs(-MAX_INT), which can
 * not be represented by int */
int solution(long n) {
    long int p;
    double pown;
    bool negative = false;
    // if n is negative, out p must be odd
    if (n < 0) {
        n = abs(n);
        negative = true;
    }

    // 2 is the smallest integer that b can be
    // and, 2^sqrt(x+1) >= x, which means that we never have to
    // look at p values bigger than sqrt(x+1)
    for (p = sqrt(n) + 1; p > 0; --p) {
        // only odd p when negative
        if (negative && p % 2 == 0) continue;
        pown = pow(n, 1 / double(p));
        // if pown is integer solution found
        if (abs(round(pown) - pown) < 0.00000000001) {
            break;
        }
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int n, res;
    while (cin >> n && n != 0) {
        res = solution(n);
        cout << res << endl;
    }

    return 0;
}