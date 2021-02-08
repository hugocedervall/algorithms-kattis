/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-08
 * @PROBLEM: unionfind
 *      The problem consists of operations on sets. Numbers
 *      can be joined with other numbers, hence joining their
 *      set. It shall be possible to query wether two numbers
 *      are in the same set or not.
 *
 *  @COMPLEXITIES:
 *      TIME: O(q*log(n))
 *          Since "find" is the most time complex operation called from
 *          both 'unionNrs" and 'same", and the complexity of "find" is
 *          O(log(n)), the complexity for both 'unionNrs" and "same" are
 *          also O(log(n)). And these operations are called q times,
 *          hence the total time complexity stated.
*/

#include <bits/stdc++.h>
#include <iostream>
#include <tuple>

using namespace std;

/**
 * Finds the root node of given x and updates x parent
 * to root node.
 *
 * @param parents mapping from each number to a parent
 * @param x index which root node is wanted for
 * @return Root node index of @param x
 *
 * Time Complexity:
 *      O(log(n)), where n is @param parents length.
 *
 */
int find(vector<int> &parents, int x) {
    int curr = x;
    while (parents[curr] != curr) {
        curr = parents[curr];
    }
    // Move node up for performance increase
    parents[x] = curr;
    return curr;
}

/**
 * Unions the sets that @param a and @param b are
 * included in.
 *
 * @param parents mapping from each number to a parent
 * @param sizes mapping from node to set size, only kept in
 * tact for root nodes.
 *
 */
void unionNrs(vector<int> &parents, vector<int> &sizes, int a, int b) {
    int aRoot = find(parents, a);
    int bRoot = find(parents, b);
    if (aRoot == bRoot) return;
    // If root size of a is smaller than root size of b,
    // then we add a to b
    if (sizes[aRoot] < sizes[bRoot]) {
        parents[aRoot] = bRoot;
        sizes[bRoot] += sizes[aRoot];
    } // Add b to a
    else {
        parents[bRoot] = aRoot;
        sizes[aRoot] += sizes[bRoot];
    }
}

/**
 * If a and b has the same root node (in same set)
 * @param parents mapping from each number to a parent
 * @return if a and b in same set, aka if a and b has
 * same root node
 */
bool same(vector<int> &parents, int a, int b) {
    return find(parents, a) == find(parents, b);
}

/**
 * Performs operations "union" and "same" which are specified
 * in @param operations.
 *
 * @param n amount of numbers, from 0 to n-1
 * @param operations contains operations that correspons to "union"
 * or "same" for a given pair of numbers.
 * @return vector of "yes" & "no" which are derived from the "same"
 * operations
 */
vector<string> unionfind(int n, const vector<tuple<string, int, int>> &operations) {
    // Set parent of each node to themselves to begin with
    vector<int> parent(n + 1);
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    // Keep track of the sizes of each root node
    vector<int> sizes(n, 1);

    vector<string> res;
    string operation;
    int a, b;
    for (auto &op : operations) {
        operation = get<0>(op);
        a = get<1>(op), b = get<2>(op);
        if (operation == "?") {
            // If a and b are in same set or not
            res.emplace_back(same(parent, a, b) ? "yes" : "no");
        } else {
            // Make a and b same set
            unionNrs(parent, sizes, a, b);
        }
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    char operation;
    int a, b;
    vector<tuple<string, int, int>> operations(q);
    for (int i = 0; i < q; ++i) {
        cin >> operation >> a >> b;
        operations[i] = make_tuple(operation, a, b);
    }
    vector<string> res = unionfind(n, operations);
    for (auto &r : res) cout << r << '\n';
    cout << flush;
    return 0;
}

