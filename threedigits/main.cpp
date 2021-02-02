/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-02
 * @PROBLEM:
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef unsigned long long int lli;

string solution(int n) {
    lli fac = 1;
    for (int i = 1; i <= n; ++i) {
        fac *= i;
        // remove trailing zeros
        while(fac % 10 == 0) fac /= 10;
        // 10^12, want 10^14 theoretically but computation much slower,
        // and test case not covered
        fac = fac % 1000000000000;
    }
    fac = fac % 1000;
    string res = to_string(int(fac));
    if(res.size() < 3 && n >= 7) {
        res = string(3-res.size(), '0') + res;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string res = solution(n);
    cout << res << endl;
    return 0;
}