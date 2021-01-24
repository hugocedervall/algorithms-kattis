/**
 * @PROBLEM: chopwood
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-24
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

vector<int> solution(int v[], int size) {
    // Amount of "children" for each node
    unordered_map<int, int> childCounter;

    // Sorted by how cheap they are
    priority_queue<int, vector<int>, greater<>> q;

    // Counts for each node in v
    for (int i = 0; i < size; ++i) {
        if (childCounter.find(v[i]) == childCounter.end()) {
            childCounter[v[i]] = 1;
        } else childCounter[v[i]]++;
    }

    // Nodes that are not included in v, aka leafs
    for (int i = 1; i < size + 1; ++i) {
        if (childCounter.find(i) == childCounter.end())
            q.push(i);
    }
    // Not possible
    if (q.empty()) return vector<int>();

    vector<int> res(size);
    for (int i = 0; i < size; ++i) {
        if (q.empty()) return vector<int>();
        // Chop the cheapest leaf
        res[i] = q.top();
        q.pop();

        // Remove connection to chopped node
        int curr = v[i];
        childCounter[curr]--;
        // If no more connections, node is also a leaf
        if (childCounter[curr] == 0) q.push(curr);
    }
    return res;
}

int main() {
    // Make input reading faster
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    int n;
    getline(cin, line);
    n = stoi(line);

    int v[n];
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        v[i] = stoi(line);
    }
    vector<int> res = solution(v, n);
    if (res.empty() || res.size() != n) {
        cout << "Error" << endl;
    } else {
        for (int re : res) {
            cout << re << endl;
        }
    }
    return 0;
}
