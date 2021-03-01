/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-01
 * @PROBLEM: getshorty
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Edge {
    int to;
    double f;

    Edge(int to, double f) {
        this->to = to;
        this->f = f;
    }
};

double dijkstra(vector<vector<Edge>> adj) {
    int startNode = 0, endNode = adj.size() - 1;

    // Max fractions at each node
    vector<double> maxFrac(adj.size(), 0);

    // current fraction and current node
    priority_queue<pair<double, int>> q;

    q.push({1.0, startNode});

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        int currNode = curr.second;
        double currFrac = curr.first;
        if (currNode == endNode) return currFrac;

        // For each neightbour
        for (auto &n : adj[currNode]) {
            // If fraction will be bigger than found
            if (maxFrac[n.to] < currFrac * n.f) {
                maxFrac[n.to] = currFrac * n.f;
                q.push({currFrac * n.f, n.to});
            }
        }

    }
    // Should always be a solution
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // n = nr of intersections. m = nr of corridors
    int n, m;
    int x, y;
    double f;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<vector<Edge>> adj(n);
        for (int i = 0; i < m; ++i) {
            // corridor between x and y with factor f
            cin >> x >> y >> f;
            adj[x].emplace_back(y, f);
            adj[y].emplace_back(x, f);
        }
        double res = dijkstra(adj);
        cout << fixed << setprecision(4) << res << '\n';
    }

    cout << flush;

    return 0;
}