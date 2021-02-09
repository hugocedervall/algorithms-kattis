/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-08
 * @PROBLEM: fenwick
 *      The problem is to calculate the sum from 0 to i-1 given
 *      an i. The values on each position can be updated. Both
 *      these operations should be performed in log(n) time,
 *      where n is the sequence length.
 *
 * @COMPLEXITIES:
 *      TIME: O(q*log(n))
 *          Since both 'getSum' and 'updateValueFwt' have time complexities
 *          O(log(n)), the total time complexity will be O(q*log(n)) since
 *          there are q amount of operations, each with O(log(n)) complexity.
*/

#include <bits/stdc++.h>
#include <iostream>
#include <tuple>

using namespace std;


/**
 * Calculates the sum up until (not inclusive) given
 * an index and a fenwick tree, which is represented by
 * a vector.
 *
 * @param tree fenwick tree datastructure
 * @param i index to get sum up until (not inclusive)
 * @return sum of value on indexes [0, ..., i-1] in @param tree
 */
long getSum(vector<long> &tree, int i) {
    long sum = 0;
    i++;
    while (i > 0) {
        sum += tree[i];
        // Returns value of last set bit
        i -= i & (-i);
    }
    return sum;
}

/**
 * Adds the given value at the given index
 *
 * @param tree fenwick tree datastructure
 * @param i index to update value for
 * @param value will be added to the current value at index @param i
 */
void updateValueFwT(vector<long> &tree, int i, int value) {
    i++;
    while (i <= tree.size()) {
        tree[i] += value;
        // Returns value of last set bit
        i += i & (-i);
    }
}

/**
 * Updates and queries values in a fenwick tree.
 *
 * @param n length of the array
 * @param operations contains operations that correspons to 'updateValueFwT'
 * or 'getSum' functions for given numbers.
 * @return results from all queries ('getSum')
 */
vector<long> fenwick(int n, vector<tuple<string, int, int>> &operations) {
    // Since all values are 0 in beginning, there is no need to "build"
    // the fenwick tree. Size of n+1 used in order to query indexes [0, ..., n].
    vector<long> tree(n + 1, 0);

    string operation;
    int a, b;
    vector<long> res;
    for (auto &op : operations) {
        operation = get<0>(op);
        a = get<1>(op), b = get<2>(op);
        // Query
        if (operation == "?") {
            res.push_back(getSum(tree, a - 1));
        } // Increment a by b
        else {
            updateValueFwT(tree, a, b);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    string operation;
    int a, b;
    // Operation and values a and b. if operations is "+", b is
    // kept for simplicities sake, it will not be used in that case.
    vector<tuple<string, int, int>> operations(q);
    for (int i = 0; i < q; ++i) {
        cin >> operation >> a;
        if (operation == "+") { cin >> b; }
        else b = 0;
        operations[i] = make_tuple(operation, a, b);
    }
    vector<long> res = fenwick(n, operations);
    if (!res.empty()) {
        for (auto &r : res) cout << r << '\n';
        cout << flush;
    }

    return 0;
}

