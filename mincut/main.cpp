/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-01
 * @PROBLEM: mincut
 *      The problem is to find a subset U, such that the weights inbetween U and all
 *      other nodes are minimized. This is solved with max-flow which is done
 *      with Ford-Fulkersons method implemented with Edmonds–Karps algorithm.
 * @COMPLEXITIES:
 *      Time: O(|V| * |E|^2), where |V| = amount of nodes, |E| = amount of edges. This
 *      is the complexity of Edmonds-Karps algorithm, and it's the dominating factor in
 *      the algorithm compared to a dfs search afterwards.
 *
 *      Memory: O(|V|^2), saving the capacities from all nodes to all other nodes.
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Represents capacity in a edge. Used to keep track of
// used capacity and remaining capacity.
struct Cap {
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
int bfs(int s, int t, vector<int> &parent, const vector<vector<int>> &adj, vector<vector<Cap>> &caps) {
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
int maxflow(int s, int t, const vector<vector<int>> &adj, vector<vector<Cap>> &capacities) {
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

/**
 * Depth first search to find reachable nodes from given starting node.
 *
 * @param adj direct reachable nodes from given node
 * @param caps remaning and used capacities for all edges between nodes.
 * @param visited visited nodes
 * @param s current node to search from
 */
void dfs(const vector<vector<int>> &adj, vector<vector<Cap>> caps, vector<bool> &visited, const int s) {
    visited[s] = true;
    for (auto &n : adj[s])
        // Reachable if there is remaining capacity in edge
        if (!visited[n] && caps[s][n].remain > 0)
            dfs(adj, caps, visited, n);
}

/**
 * Finding a subset U with @param s included and @param t not included, such that the
 * weights between U and all nodes not in U is minimized. This is done through max-flow,
 * which maximises the capacity used from @param s to @param t. The edges where the maximum
 * flow is bottlenecked, where all the capacity are used, is also the edges which will minimize
 * the weights between the set U from the other nodes.
 *
 * @param adj adjancent nodes from node at index
 * @param capacities capacities for edges between nodes
 * @param s starting node
 * @param t ending node
 * @return subset of nodes U such that @param s is in U and t is not in U. The weights
 * between U and nodes not in U is minimized.
 */
vector<int> minCut(vector<vector<int>> &adj, vector<vector<Cap>> &caps, int s, int t) {
    int n = adj.size();

    // Dont need actual max flow, just the updated capacities
    maxflow(s, t, adj, caps);

    // Find reachable nodes from start
    vector<bool> visited(n, false);
    dfs(adj, caps, visited, s);

    // Which nodes are reachable from start node
    vector<int> reachableNodes;
    for (int i = 0; i < visited.size(); ++i)
        if (visited[i]) reachableNodes.push_back(i);

    return reachableNodes;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t, u, v, w;
    cin >> n >> m >> s >> t;

    vector<vector<int>> adj(n, vector<int>());
    // u, v to remaining and used flow
    vector<vector<Cap>> caps(n, vector<Cap>(n));
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        adj[u].push_back(v);
        // Path in other way required for algorithm
        adj[v].push_back(u);
        caps[u][v] = Cap{w, 0};
    }

    auto res = minCut(adj, caps, s, t);
    cout << res.size() << '\n';
    for (auto &r : res)
        cout << r << '\n';

    return 0;
}