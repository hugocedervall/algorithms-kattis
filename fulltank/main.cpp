/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-17
 * @PROBLEM: fulltank
*/

#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

// Edges between vertexes from and node with a given cost and tank capacity.
struct edge {
    int node, cost, tank;

    bool operator<(const edge &e) const {
        if (cost == e.cost) return tank > e.tank;
        return cost > e.cost;
    }
};

/*
 * Dijkstras algorithm to find minimum cost
 */
int shortestPath(vector<vector<edge>> &edges, vector<int> &prices, int start, int end, int capacity) {
    // The cost at given cities with capacity left
    vector<vector<int>> costs(edges.size(), vector<int>(capacity + 1, INT_MAX));
    costs[start][0] = 0;

    // pair of vertex id and minimum cost
    priority_queue<edge> q;
    // Start at given start vertex
    q.push(edge{start, 0, 0});

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();

        // If reacched destination
        if (curr.node == end) return curr.cost;
        // If already found cheaper to curr node
        if (costs[curr.node][curr.tank] < curr.cost) continue;

        // Tank 1 unit if not full and cheaper than found
        int newCost = curr.cost + prices[curr.node];
        if (curr.tank < capacity && newCost < costs[curr.node][curr.tank + 1]) {
            costs[curr.node][curr.tank + 1] = newCost;
            q.push(edge{curr.node, newCost, curr.tank + 1});
        }

        // For each neighbour of curr
        for (auto &n : edges[curr.node]) {
            // If tank is enough to reach new city
            if (curr.tank >= n.cost) {
                int currTank = curr.tank - n.cost;
                // If costs if less at new state
                if (curr.cost < costs[n.node][currTank]) {
                    costs[n.node][currTank] = curr.cost;
                    q.push(edge{n.node, curr.cost, currTank});
                }
            }
        }
    }
    // If not found path to @param end
    return INT_MAX;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, u, v, d, q, c, s, e;
    cin >> n >> m;

    // Cities/Nodes prices
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    // Roads/edges
    vector<vector<edge>> roads(n, vector<edge>());
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> d;
        roads[u].push_back(edge{v, d, 0});
        roads[v].push_back(edge{u, d, 0});
    }

    cin >> q;
    for (int _ = 0; _ < q; ++_) {
        cin >> c >> s >> e;
        int res = shortestPath(roads, prices, s, e, c);
        if (res == INT_MAX) cout << "impossible" << '\n';
        else cout << res << '\n';
    }
    cout << flush;

    return 0;
}
