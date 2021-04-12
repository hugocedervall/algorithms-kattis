/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-12
 * @PROBLEM: primesieve
 *      The problem is to find all primes in the range
 *      [1,...,n].
 * @COMPLEXITIES:
 *      TIME: O(n * log(log(n)))
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/**
 * Implementation of Sieve of Eratosthenes algorithm
 * to compute all primes from 1 to a given number.
 */
class Sieve {
private:
    vector<bool> _isPrime;
    int _nrPrimes = 0;

    /**
     * Computes all primes from 1 to @param limit. This is done
     * by marking all numbers which can not be primes. A number is
     * not a prime if it's an multiplication of a previous prime.
     *
     * @param limit compute all primes from 1 to this @param limit
     */
    void findPrimes(const int &limit) {
        _isPrime = vector<bool>(limit + 1, true);
        _isPrime[0] = _isPrime[1] = false;
        /* only going to sqrt of limit is an optimization
         which works since we always start the inner loop from
         i*i, and hence all numbers will be covered */
        for (int i = 2; i <= sqrt(limit); ++i)
            if (_isPrime[i]) {
                this->_nrPrimes++;
                // i * i can be bigger than INT_MAX
                for (long j = (long) i * i; j <= limit; j += i)
                    _isPrime[j] = false;
            }
        // Since only going to sqrt(limit), also count rest primes
        for (int i = (int) sqrt(limit) + 1; i <= limit; ++i)
            if (this->_isPrime[i])
                this->_nrPrimes++;
    }

public:
    explicit Sieve(const int &n) {
        this->findPrimes(n);
    }

    int isPrime(const int &x) {
        if (x <= _isPrime.size())
            return _isPrime[x];
        return false;
    }

    int nrPrimes() const {
        return this->_nrPrimes;
    }

};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, nr;
    cin >> n >> q;
    Sieve s = Sieve(n);

    cout << s.nrPrimes() << '\n';
    for (int i = 0; i < q; ++i) {
        cin >> nr;
        cout << s.isPrime(nr) << '\n';
    }
    cout << flush;

    return 0;
}