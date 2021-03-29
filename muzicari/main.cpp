/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-29
 * @PROBLEM: muzicari
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/**
 * Used to represent a item in the knapsack
 */
struct knapsackItem {
    int weight = 0;
};

/**
 * Dynamic solution to the knapsack problem
 * @param maxCapacity capacity that fits in the knapsack
 * @param items the items which can be put in knapsack
 * @return items that maximize the total value
 */
vector<int> knapsack(int maxCapacity, vector<knapsackItem> &items) {
    // All possible weights represented in the columns
    // the rows represent the items
    int k[items.size() + 1][maxCapacity + 1];

    // Initialize all values to 0
    for (int i = 0; i < items.size() + 1; ++i)
        for (int j = 0; j < maxCapacity + 1; ++j)
            k[i][j] = 0;

    // Dynamically compute the best value for each capacity and item
    for (int i = 0; i < items.size() + 1; ++i) {
        for (int j = 0; j < maxCapacity + 1; ++j) {
            // No value if no weight or item
            if (i == 0 || j == 0) {
                k[i][j] = 0;
            } else if (items[i - 1].weight <= j) {
                // If the current item be used instead of previous
                k[i][j] = max(items[i - 1].weight + k[i - 1][j - items[i - 1].weight],
                              k[i - 1][j]);
            } else {
                // Previous solution is still best
                k[i][j] = k[i - 1][j];
            }
        }
    }

    // Find the best solution which match res
    int res = k[items.size()][maxCapacity];
    vector<int> resItems;
    int c = maxCapacity;
    for (int i = items.size(); i > 0 && res > 0; --i) {
        // If solution is found on the row above (then result
        // was moved from that row to current row)
        if (res == k[i - 1][c])
            continue;
        resItems.push_back(i - 1);
        res -= items[i - 1].weight;
        c -= items[i - 1].weight;
    }
    return resItems;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int T, n, tmpTime = 0;
    cin >> T >> n;
    vector<knapsackItem> items(n);
    for (int i = 0; i < n; ++i) {
        cin >> tmpTime;
        items[i] = knapsackItem{tmpTime};
    }

    // The result represents the order of which persons will take breaks.
    // meanwhile the persons not specified will take brakes right after the others
    // not included in the solution
    vector<int> res = knapsack(T, items);

    // Can be seen as two queues with breaks
    int break1 = 0, break2 = 0;
    for (int i = 0; i < items.size(); ++i) {
        // If item was included in found solution
        if (find(res.begin(), res.end(), i) != res.end()) {
            cout << break1 << " ";
            break1 += items[i].weight;
        }
        // If not included in found solution
        else {
            cout << break2 << " ";
            break2 += items[i].weight;
        }
    }

    cout << '\n' << flush;

    return 0;
}