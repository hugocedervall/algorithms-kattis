/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-26
 * @PROBLEM: checkingforcorrectness
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;
typedef long long ll;


ll bigModMul(ll a, ll b, ll m) {
    ll res = 0;
    a = a % m;
    while (b > 0) {
        // if b is odd, add a to res
        if (b % 2 == 1)
            res = (res + a) % m;
        a = (a * 2) % m;
        b /= 2;
    }
    return res;
}

ll bigPlusmod(ll a, ll b, ll m) {
    return ((a % m) + b) % m;
}

ll bigPowMod(ll base, ll exponent, ll mod) {
    base %= mod;
    ll res = 1;
    while (exponent > 0) {
        if (exponent & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exponent = exponent >> 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    ll a, b;
    string op;

    // to get 4 last
    int mod = 10000;

    while (cin >> a >> op >> b) {
        if (op == "+")
            cout << bigPlusmod(a, b, mod) << '\n';
        else if (op == "*")
            cout << bigModMul(a, b, mod) << '\n';
        else
            cout << bigPowMod(a, b, mod) << '\n';

        cout << flush;
    }
    cout << flush;

    return 0;
}