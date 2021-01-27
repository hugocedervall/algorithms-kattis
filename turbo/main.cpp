/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-25
 * @PROBLEM: turbo
*/

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

/**
 * @return sum from [0,...,i]
 */
int getSum(vector<int> &tree, int i) {
    int sum = 0;
    i++;

    while (i > 0) {
        sum += tree[i - 1];
        // Returns value of last set bit
        i -= i & (-i);
    }
    return sum;
}

/**
 * @return sum from [i,...,j]
 */
int getSum(vector<int>& tree, int i, int j) {
    return fabs(getSum(tree, j) - getSum(tree, i));
}

void updateValueFwT(vector<int> &tree, int i, int value) {
    i++;
    while (i <= tree.size()) {
        tree[i - 1] += value;
        // Returns value of last set bit
        i += i & (-i);
    }
}

vector<int> buildFenwickTree(vector<int> &nums) {
    vector<int> tree(nums.size(), 0);
    for (int i = 0; i < tree.size(); ++i) {
        updateValueFwT(tree, i, nums[i]);
    }
    return tree;
}


vector<int>* solution(int n, unordered_map<int, int> &indexMapping) {
    auto *res = new vector<int>(n);
    auto init = vector<int>(n,1);
    vector<int> tree = buildFenwickTree(init);

    int dist, left = 1, right = n;
    for (int i = 0; i < n; ++i) {
        int pos;
        if (i % 2 == 0) {
            // position of number in array
            pos = indexMapping[left];
            // Amount that must be swapped
            dist = getSum(tree, pos - 1);
            left++;

        } else {
            pos = indexMapping[right];
            // Amount that must be swapped
            dist = getSum(tree, pos, n - 1);
            right--;
        }
        // Since we now have "moved" current, discard it from further
        // calculations
        updateValueFwT(tree, pos, -1);
        (*res)[i] = dist;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string line;
    int n;
    getline(cin, line);
    n = stoi(line);

    // number to index mapping
    unordered_map<int, int> indexMapping;
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        indexMapping[stoi(line)] = i;
    }

    auto res = solution(n, indexMapping);
    for (const auto r : *res) cout << r << endl;
    delete res;

    return 0;
}