/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-01
 * @PROBLEM:
*/

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long double ld;
typedef unsigned long long ull;

tuple<ull, ull> solution(string nrStr) {
    ld nr = stod(nrStr);

    ld minNumerator = INFINITY;
    ld minDenominator = INFINITY;

    // All possibilities of repeating decimals
    for (int i = 2; i < nrStr.size(); ++i) {

        string repeating = string(nrStr.begin() + i, nrStr.end());
        ld repNr = stod(repeating);

        ull moveSize1 = pow(10, nrStr.size() - 2);

        ull moveSize2 = pow(10, i - 2);

        // Add the decimals, since floating errors can otherwise affect result
        ld nr1 = nr * moveSize1 + (repNr * pow(10, -ld(repeating.size())));
        ld nr2 = nr * moveSize2;

        ull top = floor(nr1) - floor(nr2);
        ull bot = moveSize1 - moveSize2;

        // Reduce fraction as much as possible
        ull gcd1 = __gcd(top, bot);
        top /= gcd1;
        bot /= gcd1;
        // Check if smallest denominator found
        if (bot < minDenominator) {
            minNumerator = top;
            minDenominator = bot;
        }

    }
    return make_tuple(minNumerator, minDenominator);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    double nr;
    string replace = "...";
    while (getline(cin, line) && line != "0") {
        auto indx = line.find(replace);
        line.replace(indx, replace.size(), "");
        auto res = solution(line);
        cout << get<0>(res) << "/" << get<1>(res) << "\n";
    }


    return 0;
}