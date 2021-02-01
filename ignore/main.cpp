/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-01
 * @PROBLEM: ignore
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;


string solution(int n) {
    // Flipped numbers which make sense
    vector<int> valid = {0, 1, 2, 5, 9, 8, 6};
    string res;
    do {
        int rest = n % valid.size();
        res += to_string(valid[rest]);
        n /= valid.size();
    } while (n != 0);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        cout << solution(n) << endl;
    }

    return 0;
}