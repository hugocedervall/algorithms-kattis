/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-22
 * @PROBLEM: happyprime
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

bool isPrime(int x) {
    if (x <= 1) return false;
    for (int i = 2; i < sqrt(x) + 1; ++i)
        if (x % i == 0) return false;
    return true;
}

bool solution(int x) {
    // Must be prime to be a happy prime!
    if (!isPrime(x)) return false;

    string nrStr = to_string(x);
    unordered_map<int, bool> visited;
    while (x != 1) {
        // If gone in cycle
        if (visited.find(x) != visited.end())
            return false;
        visited[x] = true;

        nrStr = to_string(x);
        x = 0;

        for (char &c : nrStr)
            x += pow(stoi(string(1, c)), 2);
    }
    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, m;
    cin >> n;
    while (n--) {
        cin >> k >> m;
        auto res = solution(m);
        cout << k << " " << m << " " << (res ? "YES" : "NO") << '\n';
    }
    cout << flush;

    return 0;
}
