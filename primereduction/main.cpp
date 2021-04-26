/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-26
 * @PROBLEM: primereduction
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if(n%2 == 0) return false;
    for (int i = 3; i < sqrt(n)+1; i+=2) if (n % i == 0) return false;
    return true;
}

int primeFactors(int n) {
    int res = 0;

    while (n % 2 == 0) {
        res += 2;
        n /= 2;
    }

    for (int i = 2; i < sqrt(n)+1; ++i) {
        while (n % i == 0) {
            res += i;
            n /= i;
        }
    }

    if(n > 1) res += n;

    return res;
}


pair<int, int> solution(int n, int count) {
    if (isPrime(n)) return {n, count+1};
    int newNr = primeFactors(n);
    return solution(newNr, count + 1);;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int n;
    while (cin >> n && n != 4) {
        auto res = solution(n, 0);
        cout << res.first << " " << res.second << '\n';
        cout << flush;
    }
    cout << flush;


    return 0;
}