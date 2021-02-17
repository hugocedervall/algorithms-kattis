/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-17
 * @PROBLEM: shortestpath1
 *      Standard shortest path problem from a given start vertex. This has been
 *      solved by a standard Dijkstras implementation with a priority queue.
 *
 *  @COMPLEXITIES:
 *      Time: O((E+V)*log(V)), where E is number of edges and V number of vertexes.
 *          The implementation uses adjacency lists and priority queue which results
 *          in the above time complexity.
*/

#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

// Edges between vertexes from and to with a given weight.
struct edge {
    int from, to, weight;
};

/**
 * Calculates the shortest path from @param start to all reachable nodes.
 * Nodes which are not reachable will have the distance of INT_MAX.
 *
 * @param edges mapping from vertex to all its outgoing edges
 * @param start from which vertex the path will be calculated.
 * @param n amount of vertextes in graph
 * @returns distances to all vertexes from given @param start vertex. Vertexes
 * which are not reachable will have distance INT_MAX.
 */
vector<int> shortestPath(vector<vector<edge>> &edges, const int &start, int n) {
    vector<int> distances(n, INT_MAX);
    // Distance from start to itself is 0
    distances[start] = 0;

    // Custom compare function for priority queue, will sort in increasing
    // order based on the distance to vertex.
    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
        if (a.second == b.second) return a.first > b.first;
        return a.second > b.second;
    };

    // pair of vertex id and minimum cost
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    // Start at given start vertex
    q.push(make_pair(start, distances[start]));

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();

        // For each neighbour of curr
        for (auto &n : edges[curr.first]) {
            int newDist = curr.second + n.weight;
            // If there is a shorter distance to vertex than previously discovered
            if (newDist < distances[n.to]) {
                distances[n.to] = newDist;
                q.push(make_pair(n.to, newDist));
            }
        }
    }
    return distances;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q, s, u, v, w, query;
    while (cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) break;

        // Mapping from node id to edges out from node
        vector<vector<edge>> edges(n, vector<edge>());
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            edges[u].push_back(edge{u, v, w});
        }

        // Distances from startnode to each other node
        auto distances = shortestPath(edges, s, n);

        // Handle queries
        for (int i = 0; i < q; ++i) {
            cin >> query;
            // If there is a path to given query node, print distance
            if (query >= 0 && query < n && distances[query] != INT_MAX) {
                cout << distances[query] << '\n';
            } else {
                cout << "Impossible" << '\n';
            }
        }
    }
    cout << flush;

    return 0;
}