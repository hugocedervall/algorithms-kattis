/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-17
 * @PROBLEM: shortestpath3
 *      Shortest path problem from a given start vertex with constraints on edges where
 *      weights can be negative.  This has been solved with Bellman-Ford's algorithm.
 *
 *  @COMPLEXITIES:
 *      Time: O(|E| * (|E| + |V|)). |V| = nr of vertices, |E| = nr of edges.
 *          Bellman-Ford algorithm is O(|V| * |E|), where |V| is nr of vertices and |E|
 *          is number of edges. When checking for cycles in the graph, a BFS is performed,
 *          which has a time complexity of O(|V| + |E|). In worst case the BFS might be performed
 *          |E| times, which leads to a time complexity of O(|E|*(|V| + |E|)), which makes
 *          the total time complexity.
*/

#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

/**
 * Edges between vertexes from and to with a given weight.
 */
struct edge {
    int from, to, weight;
};

/**
 * Calculates the shortest path from @param start to all reachable nodes.
 * Nodes which are not reachable will have the distance of INT_MAX. Nodes
 * which are reachable from a negative cycle will have the distance -INT_MAX.
 *
 * @param edges all edges in graph
 * @param nodeEdges mapping from vertex to all its outgoing edges
 * @param start from which vertex the path will be calculated.
 * @returns distances to all vertexes from given @param start vertex. Vertices
 * which are not reachable will have distance INT_MAX. Vertices which are
 * reachable from a negative cycle will have the dinstance -INT_MAX.
 */
pair<vector<int>, vector<int>>
shortestPath(vector<edge> &edges, vector<vector<edge>> &nodeEdges, const int &start) {
    vector<int> distances(nodeEdges.size(), INT_MAX);
    vector<int> parents(nodeEdges.size(), -1);
    // Distance from start to itself is 0
    distances[start] = 0;
    parents[start] = start;

    for (int i = 1; i < nodeEdges.size(); ++i) {
        for (int j = 0; j < edges.size(); ++j) {
            int u = edges[j].from, v = edges[j].to;
            int weight = edges[j].weight;
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                parents[v] = u;
            }
        }
    }

    // Check for cycles which are negative in weights
    for (auto &edge : edges) {
        int u = edge.from, v = edge.to;
        int weight = edge.weight;
        // Since all should already be minimal, they must be negative cycle if found
        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            // BFS search to find all reachable nodes from current. All
            // reachable vertices will get -INF in cost.
            queue<int> q;
            vector<int> marked(nodeEdges.size());
            q.push(u);
            while (!q.empty()) {
                int curr = q.front();
                q.pop();

                // For each outgoing edge
                for (auto &e : nodeEdges[curr]) {
                    // If not visited and not already negative inf
                    if (!marked[e.to] && distances[e.to] != -INT_MAX) {
                        q.push(e.to);
                        distances[e.to] = -INT_MAX;
                        marked[e.to] = true;
                    }
                }
            }
        }
    }
    return make_pair(distances, parents);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q, s, u, v, w, query;
    while (cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) break;

        // Mapping from node id to edges out from node
        vector<vector<edge>> nodeEdges(n, vector<edge>());
        vector<edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            edge e = edge{u, v, w};
            edges[i] = e;
            nodeEdges[u].push_back(e);
        }

        // Distances from startnode to each other node
        auto distances = shortestPath(edges, nodeEdges, s).first;

        // Handle queries
        for (int i = 0; i < q; ++i) {
            cin >> query;
            // If there is a path to given query node, print distance
            if (query >= 0 && query < n && distances[query] != INT_MAX && distances[query] != -INT_MAX) {
                cout << distances[query] << '\n';
            } else if (distances[query] == INT_MAX) {
                cout << "Impossible" << '\n';
            } else if (distances[query] == -INT_MAX) {
                cout << "-Infinity" << '\n';
            }
        }
    }
    cout << flush;

    return 0;
}