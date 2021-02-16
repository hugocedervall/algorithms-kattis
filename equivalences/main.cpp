/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-16
 * @PROBLEM: equivalences
*/

#include <bits/stdc++.h>
#include <iostream>
#include <stack>

using namespace std;

/**
 * Tarjan's strongly connected components algorithm
 *
 * Recursive DFS implementation that finds strongly connected components.
 * Keeps track of which component each node is connected to.
 */
void SCC(int u, unordered_map<int, vector<int>> &vertexes, vector<bool> &onStack, stack<int> &s,
         vector<int> &cheapest, vector<int> &cost, int &scCount, unordered_map<int, vector<int>> &sccNodes,
         vector<int> &nodeSCCID, int &time) {
    s.push(u);
    onStack[u] = true;

    cost[u] = cheapest[u] = ++time;

    // For each outgoing edge
    for (auto &v : vertexes[u]) {
        if (cost[v] == -1) {
            SCC(v, vertexes, onStack, s, cheapest, cost, scCount, sccNodes, nodeSCCID, time);
            cheapest[u] = min(cheapest[u], cheapest[v]);
        } else if (onStack[v]) {
            cheapest[u] = min(cheapest[u], cheapest[v]);
        }
    }

    int w;
    if (cheapest[u] == cost[u]) {
        while (s.top() != u) {
            w = s.top();
            onStack[w] = false;
            s.pop();
            sccNodes[scCount].push_back(w);
            nodeSCCID[w] = scCount;
        }
        w = s.top();
        onStack[w] = false;
        s.pop();
        sccNodes[scCount].push_back(w);
        nodeSCCID[w] = scCount;

        scCount++;
    }
}

// Finds strongly connected components
int solution(int nrNodes, unordered_map<int, vector<int>> &vertexes) {
    if (nrNodes <= 1) return 0;
    // Mapping from SCC ID to sccNodes
    unordered_map<int, vector<int>> sccNodes;

    // Stack of vertexes
    stack<int> s;
    // Keep track of which vertexes that are on stack
    vector<bool> onStack(nrNodes, false);
    // Mapping from node to which SCC (component) ID it belongs to
    vector<int> nodeSSCID(nrNodes, -1);
    // Used in DFS,
    vector<int> cheapest(nrNodes, -1);
    vector<int> cost(nrNodes, -1);

    // Start from arbitary vertex
    s.push(0);
    onStack[0] = true;

    int res = 0, time = 0;
    for (int i = 0; i < nrNodes; ++i) {
        if (cost[i] == -1) {
            SCC(i, vertexes, onStack, s, cheapest, cost, res, sccNodes, nodeSSCID, time);
        }
    }

    // Count all incoming/outgoing edges from/to each strong component
    vector<int> in(res, 0), out(res, 0);
    for (int r = 0; r < res; ++r) {
        // Each node in current SSC (component)
        for (auto &i : sccNodes[r]) {
            // Each outgoing from curr node
            for (auto &j : vertexes[i]) {
                // If not going to itself
                if (nodeSSCID[i] != nodeSSCID[j]) {
                    // Increase out-/in-going amount to each component
                    out[nodeSSCID[i]] += 1;
                    in[nodeSSCID[j]] += 1;
                }
            }
        }
    }
    int intZeroCount = 0, outZeroCount = 0;
    if (res > 1)
        for (int i = 0; i < res; ++i) {
            if (in[i] == 0) intZeroCount++;
            if (out[i] == 0) outZeroCount++;
        }
    return max(intZeroCount, outZeroCount);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tst, n, m, from, to;
    cin >> tst;
    for (int _ = 0; _ < tst; ++_) {
        cin >> n >> m;

        unordered_map<int, vector<int>> vertexes;

        for (int i = 0; i < m; ++i) {
            cin >> from >> to;
            // transform to nodes [0,..,m-1] instead of [1,..,m]
            from--, to--;
            //edges[i] = edge{from, to};
            vertexes[from].push_back(to);
        }
        int res = solution(n, vertexes);
        cout << res << '\n';
    }
    cout << flush;
    return 0;
}