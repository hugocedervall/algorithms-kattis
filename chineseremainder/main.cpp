/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-12
 * @PROBLEM: chineseremainder
 *      The problem is to find the minimal integer x, such that
 *      x = a (mod n) and x = b (mod m), where m and n are
 *      relative prime. The solution is based on
 *      the inverse modulu of m and n.
 *
 * @COMPLEXITIES:
 *     TIME: n*log(n)
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;

/**
 * Calculated the modulus operation of a % b.
 * Also handles negative numbers.
 */
ll mod(ll a, ll b) {
    return (b + (a % b)) % b;
}

/**
 * Computes the greatest common dicisor (GCD) of two integers,
 * and finds a way to represent the GCD in terms of a and b. The
 * results will be: a*x + b*y = gcd(a,b)
 *
 * @param a The first integer to compute gcd for
 * @param b The second integer to compute gcd for
 * @param x Where result of first coefficient will be inserted
 * @param y Where result of second coefficient will be inserted
 * @return
 */
ll extendedEucliden(ll a, ll b, ll *x, ll *y) {
    if (b == 0) {
        *x = 1, *y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extendedEucliden(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - y1 * (a / b);
    return gcd;
}

/**
 * Calculates x such that a*x = 1 (mod m). In other words,
 * calculate the modular multiplicative inverse x of a such that
 * the product a*x is congurent to 1 modulo m.
 *
 * @param a The number to calculate the corresponding multiplicative
 * inverse of.
 * @param m modulus
 * @return the modulo inverse of @param a
 */
ll modInv(ll a, ll m) {
    ll x, y;
    ll reduction = extendedEucliden(a, m, &x, &y);
    // No solution if reduction isn't 1
    if (reduction != 1)
        return -1;
    return mod(x, m);
}

/**
 * Calculates (a*b) mod m without overflow. This is done by
 * using the following logic:
 *    if b is even:
 *      a * b = 2 * a * (b / 2),
 *    else:
 *      a * b = a + a * (b - 1)
 *
 * @param a first multiplication value
 * @param b second multiplication value
 * @param m modulu value
 * @return @param a multiplied with @param b modulo @param m, (a*b) mod m.
 */
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

/**
 * Calculates the minimum value for a variable x such that x = a (mod n)
 * and x = b (mod m) where m and n are relative prime.
 *
 * @return m * n, and x (see properties above)
 */
pair<ll, ll> findMinX(ll a, ll n, ll b, ll m) {
    ll K = n * m;

    ll x = bigModMul(a * modInv(m, n), m, K);
    x += bigModMul(b * modInv(n, m), n, K);

    return {mod(x, K), K};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    ll a, n, b, m;
    cin >> T;
    while (T--) {
        // stated that: gcd(n,m) = 1
        cin >> a >> n >> b >> m;
        auto res = findMinX(a, n, b, m);
        cout << res.first << " " << res.second << '\n';
    }
    cout << flush;

    return 0;
}