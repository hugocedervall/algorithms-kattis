/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-23
 * @PROBLEM: minspantree
 *      The problem is to find the minimum spanned tree in
 *      a given graph. This is solved with Prim’s Minimum
 *      Spanning Tree algorithm.
 *
 * @COMPLEXITIES:
 *      TIME: O((N + E) * log(N)), where N = amount of nodes, E = amount of edges
 *          This is the time complexity of Prim’s Minimum Spanning Tree algorithm.
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/**
 * Edge representes an edge between two nodes with a given weigt
 */
struct Edge {
    int from, to, weight;

    Edge(int from, int to, int weight = 0) {
        this->from = from, this->to = to, this->weight = weight;
    }

    // Sort based on weight in first hand, then sort based on from and to nodes
    bool operator<(const Edge &e) const {
        if (weight == e.weight) return from == e.from ? from > e.from : to > e.to;
        return weight > e.weight;
    }
};

/**
 * Calculates the minimum spanning tree according to
 * Prim’s Minimum Spanning Tree algorithm.
 *
 * @param adj mapping of adjencent nodes from given index node
 * @return pair of total weight in minimum spanning tree
 *  and all edges used in that tree.
 */
pair<int, vector<Edge>> mst(vector<vector<Edge>> &adj) {
    vector<Edge> resTree;
    int res = 0;

    vector<bool> marked(adj.size(), false);

    // Mark first node
    marked[0] = true;

    // If no nodes or no neighbours to node 0
    if (adj.empty() || adj[0].empty()) return {-1, resTree};

    priority_queue<Edge> q;
    // Initially push all neighbours to first node
    for (int i = 0; i < adj[0].size(); ++i)
        q.push(adj[0][i]);

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();

        if (marked[curr.to])
            continue;

        // Current edge is guaranteed to be the cheapest that
        // connects to a new node
        marked[curr.to] = true;
        // add edge from smaller node id to larger node id
        resTree.emplace_back(min(curr.from, curr.to), max(curr.from, curr.to));
        res += curr.weight;

        // Look at all unmarked neighbours
        for (auto &n : adj[curr.to]) {
            if (!marked[n.to]) {
                q.push(n);
            }
        }
    }
    return {res, resTree};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<vector<Edge>> adj(n, vector<Edge>());
        int u, v, w;
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            adj[u].emplace_back(u, v, w);
            adj[v].emplace_back(v, u, w);
        }

        auto res = mst(adj);
        if (res.first != -1 && res.second.size() == n - 1) {
            cout << res.first << '\n';
            // Sort edges based on increasing node numbering
            auto cmp = [](const Edge &a, const Edge &b) {
                if (a.from == b.from) return a.to < b.to;
                return a.from < b.from;
            };
            sort(res.second.begin(), res.second.end(), cmp);
            for (auto &r : res.second) {
                cout << r.from << " " << r.to << '\n';
            }
        } else {
            cout << "Impossible" << '\n';
        }
    }
    cout << flush;

    return 0;
}