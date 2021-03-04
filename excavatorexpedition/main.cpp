/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-04
 * @PROBLEM: excavatorexpedition
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Edge {
    int from, to, weight = 0;
};

pair<vector<int>, vector<int>> shortestPath(vector<vector<Edge>> &edges, const int &start) {
    int n = edges.size();
    vector<int> distances(n, INT_MAX);
    vector<int> parents(n, -1);
    // Distance from start to itself is 0
    distances[start] = 0;
    parents[start] = start;

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
                parents[n.to] = curr.first;
                q.push(make_pair(n.to, newDist));
            }
        }
    }
    return make_pair(distances, parents);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int v, e;
    cin >> v >> e;

    vector<int> funny(v, 0);
    char tmp;
    for (int i = 0; i < v; ++i) {
        cin >> tmp;
        if (tmp == 'X') funny[i] = -1;
        else funny[i] = 1;
    }

    vector<Edge> edges;
    vector<vector<Edge>> adj(v, vector<Edge>());
    int a, b;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b;
        Edge e = Edge{a, b, funny[b]};
        adj[a].push_back(e);
        edges.push_back(e);
    }

    int start = 0, end = v - 1;

    auto res = shortestPath(adj, start);
    auto parents = res.second;
    auto distances = res.first;

    int happyness = distances[parents[end]];

    cout << -happyness << endl;

    return 0;
}