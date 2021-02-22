/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-22
 * @PROBLEM: maxflow
 *      The problem is to find the maximum flow between two given
 *      nodes in a network. This is solved with Ford-Fulkerson method
 *      with Edmonds–Karp algorithm which is based on consecutive BFS searches.
 *
 * @COMPLEXITIES:
 *      Time: O(|V| * |E|^2), where |V| = amount of nodes, |E| = amount of edges
 *      Memory: O(|V|^2)
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Represents capacity in a edge. Used to keep track of
// used capacity and remaining capacity.
struct cap {
    int remain = 0, used = 0;
};

/**
 * Searches network for a maximum flow from @param s and @param t. This is
 * solved with a basic BFS search.
 *
 * @param s start node
 * @param t end node
 * @param parent parents for each node in path will be inserted into vector. All nodes
 * which are not included in path will have parent -1
 * @param adj adjancent nodes from node at index
 * @param caps capacities between nodes
 * @return maximum flow in one path from s to t through the network
 */
int bfs(int s, int t, vector<int> &parent, const vector<vector<int>> &adj, vector<vector<cap>> &caps) {
    // Reset parents
    fill(parent.begin(), parent.end(), -1);

    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        // If in end node, return remain found flow
        if (curr.first == t) return curr.second;

        // For each neighbour of curr
        for (auto &n : adj[curr.first]) {
            // If not marked and still have capacity
            //if (parent[n] == -1 && caps[curr.first][n].used < caps[curr.first][n].remain) {
            if (parent[n] == -1 && caps[curr.first][n].remain > 0) {
                parent[n] = curr.first;
                int new_flow = min(curr.second, caps[curr.first][n].remain);
                //if (n == t) return new_flow;
                q.push({n, new_flow});
            }
        }
    }
    return 0;
}

/**
 * Calculates the total maximum flow between @param s and @param t. This is
 * done through consecutive BFS searches which are then added up. The method
 * is Ford-Fulkersons method implemented with Edmonds–Karps algorithm.
 *
 * @param s start node
 * @param t end node
 * @param adj adjancent nodes from node at index
 * @param capacities capacities between nodes
 * @return maximum total flow from node @param s to @param t
 */
int maxflow(int s, int t, const vector<vector<int>> &adj, vector<vector<cap>> &capacities) {
    // Keep track of parents to nodes in path
    vector<int> parents(adj.size(), -1);

    int flow = 0, new_flow;
    // For as long as there is still room for flow between s and t
    while ((new_flow = bfs(s, t, parents, adj, capacities)) != 0) {
        // Maximum flow found from start to end
        flow += new_flow;
        int curr = t;
        // Update flow used for each node on path
        while (curr != s) {
            int prev = parents[curr];
            capacities[prev][curr].used += new_flow;
            capacities[prev][curr].remain -= new_flow;
            capacities[curr][prev].used -= new_flow;
            capacities[curr][prev].remain += new_flow;

            curr = prev;
        }
    }
    return flow;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t, u, v, c;
    cin >> n >> m >> s >> t;

    vector<vector<int>> adj(n, vector<int>());
    // u, v to remaining and used flow
    vector<vector<cap>> caps(n, vector<cap>(n));
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> c;
        adj[u].push_back(v);
        // Path in other way required for algorithm
        adj[v].push_back(u);
        caps[u][v] = cap{c, 0};
    }
    int res = maxflow(s, t, adj, caps);

    // Find all nodes which were used in the total flow
    vector<tuple<int, int, int>> usedNodes;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            if (caps[i][j].used > 0)
                usedNodes.emplace_back(i, j, caps[i][j].used);
        }
    }
    cout << n << " " << res << " " << usedNodes.size() << '\n';
    // Print used flow in each edge that has flow
    for (auto &r : usedNodes)
        cout << get<0>(r) << ' ' << get<1>(r) << ' ' << get<2>(r) << '\n';
    cout << flush;

    return 0;
}
