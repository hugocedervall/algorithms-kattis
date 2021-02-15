/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-15
 * @PROBLEM: frogger
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int solution(vector<vector<char>> &gMap, int rounds) {

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests, x, n, m;
    cin >> tests;

    for (int i = 0; i < tests; ++i) {
        cin >> x >> n >> m;
        vector<vector<char>> gMap(n + 2, vector<char>(m));
        for (int xCord = 0; xCord < n + 2; ++xCord) {
            for (int yCord = 0; yCord < m; ++yCord) {
                cin >> gMap[xCord][yCord];
            }
        }

        int res = solution(gMap, x);
        if (res == -1) cout << "The problem has no solution." << '\n';
        else cout << "The minimum number of turns is " << res << "." << '\n';

    }
    cout << flush;

    return 0;
}