/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-11
 * @PROBLEM:
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int solution(vector<tuple<int, int>> &prefs) {
    // Sort based on interval end in first hand
    auto comp = [](tuple<int, int> x, tuple<int, int> y) {
        int x1 = get<0>(x), x2 = get<1>(x);
        int y1 = get<0>(y), y2 = get<1>(y);
        if (x2 == y2) {
            return x1 < y1;
        }
        return x2 < y2;
    };

    sort(prefs.begin(), prefs.end(), comp);

    int nrRooms = 0;
    int threshold = 0;
    for (int i = 0; i < prefs.size(); ++i) {
        // Since sorted on second, whenever over threshold
        // we need a new room
        if (get<0>(prefs[i]) > threshold) {
            threshold = get<1>(prefs[i]);
            nrRooms++;
        }
    }


    return nrRooms;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int n, tmp1, tmp2;
    cin >> n;
    vector<tuple<int, int>> prefs;
    for (int i = 0; i < n; ++i) {
        cin >> tmp1 >> tmp2;
        prefs.emplace_back(tmp1, tmp2);
    }

    int res = solution(prefs);
    cout << res << endl;

    return 0;
}