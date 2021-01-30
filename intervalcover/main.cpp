/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-28
 * @PROBLEM: intervalcover
 *
 * Time complexity: O(n*log(n))
*/

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;


struct interval {
    double low;
    double high;
    int initialIndex = -1;

    bool operator<(const interval &a) const {
        if (low == a.low) {
            return high < a.high;
        }
        return low < a.low;
    }
};

vector<int> cover(interval coverInterval, vector<interval> &intervals) {
    vector<interval> res;

    // Sort the intervals
    // complexity: O(n log(n))
    sort(intervals.begin(), intervals.end());

    interval bestInterval{};
    double threshold = coverInterval.low;
    bool bestSet = false;
    double bestHigh;
    interval curr{};
    for (int i = 0; i < intervals.size(); ++i) {
        curr = intervals[i];

        if (curr.low <= threshold && coverInterval.high <= curr.high) {
            res.push_back(curr);
            break;
        }

        // last best was best to threshold
        if (curr.low > threshold) {
            if (bestInterval.initialIndex == -1) return vector<int>();
            res.push_back(bestInterval);
            threshold = bestHigh;
            bestInterval = interval{};
        }

        // If found one closer to threshold
        if (curr.low <= threshold && (!bestSet || bestHigh < curr.high)) {
            bestHigh = curr.high;
            bestInterval = curr;
            bestSet = true;
            if (i == intervals.size() - 1) res.push_back(bestInterval);
        }
    }

    if (!res.empty()) {
        double start = res[0].low;
        double end = res[res.size() - 1].high;

        if (start > coverInterval.low || end < coverInterval.high) return vector<int>();

    } else return vector<int>();

    vector<int> res2(res.size());
    for (int i = 0; i < res.size(); ++i)
        res2[i] = res[i].initialIndex;
    return res2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    double low, high, tmpLow, tmpHigh;
    int n;
    while (cin >> low >> high) {
        cin >> n;
        vector<interval> intervals(n);
        for (int i = 0; i < n; ++i) {
            cin >> tmpLow >> tmpHigh;
            intervals[i] = interval{tmpLow, tmpHigh, i};
        }
        vector<int> res = cover(interval{low, high}, intervals);
        if (res.empty()) {
            cout << "impossible" << endl;
        } else {
            cout << res.size() << endl;
            for (const auto &r : res)
                cout << r << " ";
            cout << endl;
        }
    }
    return 0;
}