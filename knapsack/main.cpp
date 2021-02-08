/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-06
 * @PROBLEM: knapsack
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct knapsackItem {
    int value = 0;
    int weight = 0;
    int index = 0;
};

/**
 * Dynamic solution to the knapsack problem
 * @param capacity
 * @param items
 * @return
 */
vector<int> knapsack(int capacity, vector<knapsackItem> &items) {
    int k[items.size() + 1][capacity + 1];

    // Initialize all values to 0
    for (int i = 0; i < capacity + 1; ++i)
        for (int j = 0; j < items.size() + 1; ++j)
            k[i][j] = 0;

    for (int i = 0; i < items.size() + 1; ++i) {
        for (int j = 0; j < capacity + 1; ++j) {
            if (i == 0 || j == 0) {
                k[i][j] = 0;
            } else if (items[i - 1].weight <= j) {
                k[i][j] = max(items[i - 1].value + k[i - 1][j - items[i - 1].weight],
                              k[i - 1][j]);
            } else {
                k[i][j] = k[i - 1][j];
            }

        }
    }
    //cout << k[items.size()][capacity] << endl; //'\n';

    int res = k[items.size()][capacity];
    vector<int> resItems;

    int c = capacity;
    for (int i = items.size(); i > 0 && res > 0; --i) {
        if (res == k[i - 1][c])
            continue;

        resItems.push_back(items[i - 1].index);

        res -= items[i - 1].value;
        c -= items[i - 1].weight;
    }
    sort(resItems.begin(), resItems.end());
    return resItems;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int c, n;
    int tmpValue, tmpWeight;
    while (cin >> c >> n) {
        vector<knapsackItem> items(n);
        for (int i = 0; i < n; ++i) {
            cin >> tmpValue >> tmpWeight;
            items[i] = knapsackItem{tmpValue, tmpWeight, i};
        }
        vector<int> res = knapsack(c, items);
        if(!res.empty()) {
            cout << res.size() << '\n';
            for (int re : res) cout << re << " ";
            cout << '\n' << flush;
        }
    }

    return 0;
}


