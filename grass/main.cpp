/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-29
 * @PROBLEM: grass
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/* interval is used to represent an interval where low <= high */
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

/**
 * @param coverInterval the interval that shall be covered
 * @param intervals intervals used to cover @param coverInterval
 * @return indexes of intervals required to cover @param coverInterval with
 * minimum amount of intervals.
 */
vector<int> cover(interval coverInterval, vector<interval> intervals) {
    vector<interval> res;

    // Sort the intervals based on left interval value
    // complexity: O(n log(n))
    sort(intervals.begin(), intervals.end());

    interval bestInterval{};
    double threshold = coverInterval.low;
    bool bestSet = false;
    double bestHigh;
    interval curr{};
    // Time complexity O(n)
    for (int i = 0; i < intervals.size(); ++i) {
        curr = intervals[i];
        // If solution
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
    double low, high, pos, radius, l, w;
    int n;
    while (cin >> n >> l >> w) {
        vector<interval> intervals(n);
        for (int i = 0; i < n; ++i) {
            cin >> pos >> radius;

            if (radius < w / 2) continue;

            double d = sqrt(pow(radius, 2) - pow(w / 2, 2));
            low = max(double(0), pos - d);
            high = min(pos + d, l);
            intervals[i] = interval{low, high, i};
        }
        vector<int> res = cover(interval{0, (double) l}, intervals);
        // find initial indexes
        if (res.empty() || intervals[res[res.size() - 1]].high < l) {
            cout << "-1" << endl;
        } else {
            cout << res.size() << endl;
        }
    }


    return 0;
}