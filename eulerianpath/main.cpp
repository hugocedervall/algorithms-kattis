/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-02
 * @PROBLEM: eulerianpath
 *      Find a euler path in a graph with directed edges. A euler path
 *      is a path which visits every edge only once, but can visit
 *      vertices multiple times. This is solved with Hierholzer's Algorithm.
 *
 * @COMPLEXITIES:
 *      TIME: O(|V| + |E|), where |V|=nr of vertices, |E| = nr of edges.
 *          This is the time complexity of Hierholzer's Algorithm.
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Represents a edge between two nodes
struct Edge {

    int from, to;
    bool marked;

    Edge(int from, int to) {
        this->from = from, this->to = to, this->marked = false;
    }
};

// A Graph is used to represent nodes with outgoing edges
struct Graph {
    vector<vector<Edge>> adj;

    explicit Graph(int n) {
        this->adj = vector<vector<Edge>>(n);
    }

    void addEdge(int from, int to) {
        adj[from].emplace_back(from, to);
    }

    /**
     * @return incoming degrees and outgoing degrees
     */
    pair<vector<int>, vector<int>> getDegrees() {
        vector<int> inDegs(adj.size(), 0);
        vector<int> outDegs(adj.size(), 0);
        for (auto &a : adj)
            for (auto &e : a)
                // If not marked, it is still useable
                if (!e.marked) {
                    inDegs[e.to]++;
                    outDegs[e.from]++;
                }
        return {inDegs, outDegs};
    }

    bool isMarked(int u, int i) {
        return adj[u][i].marked;
    }

    void mark(int u, int i) {
        adj[u][i].marked = true;
    }
};

/**
 * Eulerian path solved with Hierholzer's Algorithm.
 *
 * @param g Graph to find eulerian path in
 * @return eulerian path if there is one, else
 * empty path.
 */
vector<int> eulerianPath(Graph &g) {
    if (g.adj.empty()) return vector<int>();

    // Eulerian path only if nr of nodes with odd degree is 0 or 2
    int startnode = 0;
    auto degs = g.getDegrees();
    vector<int> inDegs = degs.first;
    vector<int> outDegs = degs.second;
    // Check that there is one node which has indegree+1=outdegree
    // and only one node which has indegree=outdegree+1
    int an = -1, bn = -1;
    int nrOdd = 0;
    for (int i = 0; i < inDegs.size(); ++i) {
        if ((inDegs[i] + outDegs[i]) % 2 != 0) nrOdd++;
        if (inDegs[i] + 1 == outDegs[i]) {
            if (an != -1) return vector<int>();
            an = i;
        } else if (inDegs[i] == outDegs[i] + 1) {
            if (bn != -1) return vector<int>();
            bn = i;
        }
    }
    // Continue only if there is not  or if there if already an cycle
    if ((an == -1) != (bn == -1) && (nrOdd != 0 && nrOdd != 2)) return vector<int>();

    // Add edge between the two nodes with odd degree
    if (an != -1 && bn != -1) {
        //g.addEdge(bn, an);
        startnode = an;
    }

    stack<int> s;
    s.push(startnode);
    vector<int> res;
    // Out degrees
    vector<int> deg = g.getDegrees().second;
    while (!s.empty()) {
        auto u = s.top();
        // No more neighbours
        if (deg[u] == 0) {
            res.push_back(u);
            s.pop();
        }
            // Remaining neighbours
        else {
            // Take select one outgoing edge
            for (int i = 0; i < g.adj[u].size(); ++i) {
                if (!g.isMarked(u, i)) {
                    // "remove' or mark edge
                    g.mark(u, i);
                    s.push(g.adj[u][i].to);
                    deg[u]--;
                    break;
                }
            }
        }
    }

    // See if there is any edge which is not marked
    for (int u = 0; u < g.adj.size(); ++u) {
        for (int i = 0; i < g.adj[u].size(); ++i) {
            if (!g.isMarked(u, i)) return vector<int>();
        }
    }
    // Path is reversed from algorithm
    reverse(res.begin(), res.end());

    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, u, v;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        Graph g = Graph(n);
        for (int i = 0; i < m; ++i) {
            cin >> u >> v;
            g.addEdge(u, v);
        }

        vector<int> path = eulerianPath(g);
        if (path.empty()) {
            cout << "Impossible" << '\n';
        } else {
            // Print path
            for (auto &n : path)
                cout << n << " ";
            cout << '\n';
        }
    }

    cout << flush;

    return 0;
}
