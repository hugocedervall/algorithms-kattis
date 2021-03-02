/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-22
 * @PROBLEM: mincostmaxflow
 *      The problem is to find the maximum flow between two given
 *      nodes in a network with the minimum path costs. This is solved with Ford-Fulkerson method
 *      with Edmonds–Karp algorithm which is based on consecutive Bellman-ford searches (in order
 *      to handle negative weights).
 *
 * @COMPLEXITIES:
 *      Time: O(|V|^2 * |E|^2), where |V| = amount of nodes, |E| = amount of edges
 *      Memory: O(|V|*|E|)
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Represents a edge between nodes. Used to keep track of
// capacities, path and Edge id.
struct Edge {
    // node to vector index
    int from = -1, fromIndex = -1, to = -1;
    // Capacities
    int remain = 0, used = 0, weight = 0;
    // Same id as reverse order edge
    int id = -1;
};

/**
 * Bellman-Ford search algorithm to find the cheapest path from @param s to @param t.
 * Can handle negative weights and detects negative cycles.
 *
 * @param s starting node to search from
 * @param t goal node to find path to
 * @param parent keep track of
 * @param distances Shortest found distance for each node
 * @param adj Adjancent edges from node at index
 * @return If valid path from s to t was found without any negative cycles.
 */
bool shortestPath(int s, int t, vector<Edge> &parent, vector<int> &distances, vector<vector<Edge>> &adj
) {
    // Reset parents and distances
    fill(parent.begin(), parent.end(), Edge{});
    fill(distances.begin(), distances.end(), INT_MAX);

    // nodes
    queue<int> q;
    q.push(s);

    // If node in queue or not (for performance)
    vector<bool> inQueue(adj.size(), false);

    // To find negative cycles
    vector<int> count(distances.size(), 0);

    distances[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        // For each neighbour of u
        for (Edge &e : adj[u]) {
            // If still have capacity and cheaper than found
            if (e.remain > 0 && distances[u] + e.weight < distances[e.to]) {
                parent[e.to] = e;
                distances[e.to] = distances[u] + e.weight;

                if (!inQueue[e.to]) {
                    inQueue[e.to] = true;
                    q.push(e.to);
                    count[e.to]++;
                    // Negative cycle found
                    if (count[e.to] > count.size())
                        return false;
                }
            }
        }
    }
    // If there is found path to end node or not
    return distances[t] != INT_MAX;
}


/**
 * Calculates the total maximum flow between @param s and @param t with a minimal cost.
 * This is done through consecutive consecutive Bellman-ford searches to find the
 * cheapest paths between @param s and @param t which are then added up. The method is
 * Ford-Fulkersons method implemented with Edmonds–Karps algorithm with Bellman-Ford
 * search instead of BFS.
 *
 * @param s start node
 * @param t end node
 * @param adj adjancent edges from node at index
 * @return maximum total flow from node @param s to @param t and cost of flow. Vector
 * of edges which have flow through them.
 */
tuple<int, int, vector<Edge>> maxflow(int s, int t, vector<vector<Edge>> &adj) {
    // Keep track of parents to nodes in path
    vector<Edge> parents(adj.size());
    // Shortest found distance for each node
    vector<int> distances(adj.size(), INT_MAX);

    int flow = 0, cost = 0, newFlow;
    // For as long as there is still room for flow between s and t
    while (shortestPath(s, t, parents, distances, adj)) {
        if (distances[t] == INT_MAX) break;

        // From which node, edge index
        Edge curr = parents[t];
        newFlow = curr.remain;
        // Find new flow
        while (curr.from != s) {
            Edge prev = parents[curr.from];
            newFlow = min(prev.remain, newFlow);
            curr = prev;
        }

        // Maximum flow found from start to end
        flow += newFlow;
        cost += newFlow * distances[t];

        curr = parents[t];
        // Update flow used for each node on path
        while (curr.from != -1) {
            Edge prev = parents[curr.from];

            adj[curr.from][curr.fromIndex].used += newFlow;
            adj[curr.from][curr.fromIndex].remain -= newFlow;
            // Find reversed edge with same id
            Edge reverseEdge;
            for (int i = 0; i < adj[curr.to].size(); ++i) {
                if (adj[curr.to][i].id == curr.id) {
                    reverseEdge = adj[curr.to][i];
                    break;
                }
            }
            // Decrease flow in other direction
            adj[reverseEdge.from][reverseEdge.fromIndex].used -= newFlow;
            adj[reverseEdge.from][reverseEdge.fromIndex].remain += newFlow;

            curr = prev;
        }
    }
    // Find all edges with flow
    vector<Edge> usedEdges;
    for (auto &adjs : adj)
        for (auto &e : adjs)
            if (e.used > 0)
                usedEdges.push_back(e);

    return {flow, cost, usedEdges};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t, u, v, c, w;
    cin >> n >> m >> s >> t;

    vector<vector<Edge>> adj(n, vector<Edge>());

    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> c >> w;
        // Give both edges the same ID, this is since the capacity of one has to be
        // updated at the same time as the other.
        adj[u].push_back(Edge{u, static_cast<int>(adj[u].size()), v, c, 0, w, i});
        // Path in other way required for re-directing flow
        adj[v].push_back(Edge{v, static_cast<int>(adj[v].size()), u, 0, 0, -w, i});
    }

    auto res = maxflow(s, t, adj);
    int maxFlow = get<0>(res);
    int minCost = get<1>(res);

    // The paths that were used and how much flow that was used
    vector<Edge> usedEdges = get<2>(res);

    // Since all the edges in adj contains the used capacities, the actual path can be constructed by
    // just following the edges that have used capacity.

    cout << maxFlow << " " << minCost << endl;

    return 0;
}
