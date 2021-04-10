/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-10
 * @PROBLEM: rationalarithmetic
 *      The problem is to implement a structure for
 *      rational numbers. The structure should be able
 *      to perform basic arithmetic operations without
 *      converting the rational numbers into decimal numbers.
 *
 * @COMPLEXITIES:
 *      TIME: O(log(2*n)), n = upper limit of p and q. This is
 *      the time complexity of GCD, which is perfomed at each
 *      creation of a RationalNumber.
 *
*/

#include <bits/stdc++.h>
#include <iostream>


using namespace std;

/**
 * Represents rational number (p / q) and overloads
 * arithmetic operations to calculate new rational numbers
 * by witholding the retional representation throughout.
 */
class RationalNumber {
private:
    // numinator and denominator
    long int p, q;

    /**
     * Reduces the rational number representation to the
     * minimum integer representation of p and q that witholds
     * the same rational number.
     */
    void reduce() {
        long int reduction = __gcd(p, q);
        if (reduction != 0)
            this->p /= reduction, this->q /= reduction;
        // If number is negative, represent p as negative
        if (this->q < 0 && this->p >= 0)
            this->q *= -1, this->p *= -1;
    }

public:
    RationalNumber() {
        this->p = 0, this->q = 1;
    }

    RationalNumber(long int p, long int q) {
        this->p = p, this->q = q;
        this->reduce();
    }

    friend ostream &operator<<(ostream &out, RationalNumber &nr) {
        out << nr.p << " / " << nr.q;
        return out;
    }

    RationalNumber operator+(const RationalNumber &nr) const {
        long int newQ = this->q * nr.q;
        long int p1 = this->p * nr.q, p2 = nr.p * this->q;
        return {p1 + p2, newQ};
    }

    RationalNumber operator-(const RationalNumber &nr) const {
        long int newQ = this->q * nr.q;
        long int p1 = this->p * nr.q, p2 = nr.p * this->q;
        return {p1 - p2, newQ};
    }

    RationalNumber operator/(const RationalNumber &nr) const {
        long int newP = this->p * nr.q;
        long int newQ = this->q * nr.p;
        return {newP, newQ};
    }

    RationalNumber operator*(const RationalNumber &nr) const {
        long int newP = this->p * nr.p;
        long int newQ = this->q * nr.q;
        return {newP, newQ};
    }

    bool operator<(const RationalNumber &nr) {
        if (((*this) - nr).p < 0)
            return true;
        return false;
    }

    bool operator<=(const RationalNumber &nr) {
        return (*this) < nr || (*this) == nr;
    }

    bool operator>(const RationalNumber &nr) {
        return !((*this) < nr) && !((*this) == nr);
    }

    bool operator>=(const RationalNumber &nr) {
        return (*this) > nr || (*this) == nr;
    }

    bool operator==(const RationalNumber &nr) const {
        /* We know both rational numbers are reduced
         and hence we can compare directly */
        return this->p == nr.p && this->q == nr.q;
    }

    bool operator!=(const RationalNumber &nr) const {
        return !((*this) == nr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, p, q;
    char op;
    cin >> n;
    while (n--) {
        cin >> p >> q >> op;
        auto nr1 = RationalNumber(p, q);
        cin >> p >> q;
        auto nr2 = RationalNumber(p, q);

        RationalNumber res;

        switch (op) {
            case '+':
                res = nr1 + nr2;
                break;
            case '-':
                res = nr1 - nr2;
                break;
            case '/':
                res = nr1 / nr2;
                break;
            case '*':
                res = nr1 * nr2;
                break;
            default:
                break;
        }
        cout << res << '\n';
    }
    cout << flush;

    return 0;
}