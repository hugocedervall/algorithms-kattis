/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-12
 * @PROBLEM: generalchineseremainder
 *      The problem is to find the minimal integer x, such that
 *      x = a (mod n) and x = b (mod m). n and m must not be
 *      relative prime. The solution is based on the inverse modulu
 *      of m / lcd(m,n) and n / lcd(m,n).
 *
 * @COMPLEXITIES:
 *     TIME: log(n), where n = min(a,b) (from input)
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
 * and x = b (mod m), n and m must not be relative prime.
 *
 * @return if possible solution, x (see properties above), and least
 * common multiple of m and n.
 */
tuple<bool, ll, ll> findMinX(ll a, ll n, ll b, ll m) {
    ll g = __gcd(n, m);
    // must satisfy constraint that a is congurent b mod gcd(m,n)
    if (mod(a, g) != mod(b, g))
        return {false, 0, 0};

    ll x, y;
    extendedEucliden(n / g, m / g, &x, &y);

    // least common multiple
    ll nmLcd = n / g * m;

    ll res = bigModMul(a * y, m / g, nmLcd);
    res += bigModMul(b * x, n / g, nmLcd);

    return {true, mod(res, nmLcd), nmLcd};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    ll a, n, b, m;
    cin >> T;
    while (T--) {
        cin >> a >> n >> b >> m;
        auto res = findMinX(a, n, b, m);
        if (get<0>(res))
            cout << get<1>(res) << " " << get<2>(res) << '\n';
        else
            cout << "no solution" << '\n';
    }
    cout << flush;

    return 0;
}