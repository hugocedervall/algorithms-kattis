/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-12
 * @PROBLEM: modulararithmetic
 *      The problem is to implement modular arithmetic
 *      operations between two numbers.
 *
 * @COMPLEXITIES:
 *      TIME: O(1) for add, subtract, multiply. O(n) for division.
 *
*/

#include <bits/stdc++.h>
#include <iostream>


using namespace std;

typedef long l;

/**
 * Calculated the modulus operation of a % b.
 * Also handles negative numbers.
 */
l mod(l a, l b) {
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
l extendedEucliden(l a, l b, l *x, l *y) {
    if (b == 0) {
        *x = 1, *y = 0;
        return a;
    }
    l x1, y1;
    l gcd = extendedEucliden(b, a % b, &x1, &y1);

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
l modInv(l a, l m) {
    l x, y;
    l reduction = extendedEucliden(a, m, &x, &y);
    // No solution if reduction isn't 1
    if (reduction != 1)
        return -1;
    return mod(x, m);
}

/**
 * Calculates (a+b)%m
 */
l addMod(l a, l b, l m) {
    return mod(a + b, m);
}

/**
 * Calculates (a-b)%m
 */
l subtractMod(l a, l b, l m) {
    return mod(a - b, m);
}

/**
 * Calculates (a*b)%m
 */
l multiplyMod(l a, l b, l m) {
    return mod(a * b, m);
}

/**
 * Calculates (a/b)%m. This is done through calculating
 * the modular inverse of @param b, and then calculating the
 * modular multiplicative of a and the inverse of b.
 */
l divideMod(l a, l b, l m) {
    l inv = modInv(b, m);
    if (inv != -1)
        return multiplyMod(a, inv, m);
    return -1;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    l n, t, a, b;
    char op;
    while (cin >> n && cin >> t && (n != 0 && t != 0)) {
        while (t--) {
            cin >> a >> op >> b;

            l res = -1;
            switch (op) {
                case '+':
                    res = addMod(a, b, n);
                    break;
                case '-':
                    res = subtractMod(a, b, n);
                    break;
                case '/':
                    res = divideMod(a, b, n);
                    break;
                case '*':
                    res = multiplyMod(a, b, n);
                    break;
                default:
                    break;
            }
            cout << res << '\n';
        }
    }
    cout << flush;

    return 0;
}