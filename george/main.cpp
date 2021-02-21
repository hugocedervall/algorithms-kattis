/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-17
 * @PROBLEM: george
*/

#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

/**
 * Edges between vertexes from and to with a given weight.
 * the edge can not be used in between blockStart and blockEnd
 */
struct edge {
    int from, to, weight = INT_MAX, blockStart = -1, blockEnd = -1;
};


/**
 * Modified dijkstra with constrains on when certain edges can be used
 */
vector<int> shortestPath(vector<map<int, edge>> &paths, int lukS, int lukE, int lukasTimeDelay) {
    vector<int> distances(paths.size(), INT_MAX);
    distances[lukS] = lukasTimeDelay;

    // Custom compare function for priority queue, will sort in increasing
    // order based on the distance to vertex.
    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
        if (a.second == b.second) return a.first > b.first;
        return a.second > b.second;
    };

    // pair of vertex id and minimum cost
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    // Start at given start vertex
    q.push(make_pair(lukS, distances[lukS]));

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        int currTime = curr.second;
        if (curr.first == lukE) break;

        // For each outgoing edge of curr
        for (auto &e : paths[curr.first]) {
            int to = e.first;
            edge path = e.second;

            int newDist;
            // If path is not blocked
            if (currTime < path.blockStart || currTime >= path.blockEnd) {
                newDist = currTime + path.weight;
            } else {
                newDist = path.blockEnd + path.weight;
            }
            // If there is a shorter distance to vertex than previously discovered
            if (newDist < distances[to]) {
                distances[to] = newDist;
                q.push(make_pair(to, newDist));
            }
        }
    }
    return distances;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, lukS, lukE, lukasTimeDelay, georgeCount, A, B, L, tmp;
    cin >> n >> m;
    cin >> lukS >> lukE >> lukasTimeDelay >> georgeCount;
    lukS--, lukE--;

    vector<int> georgePath(georgeCount, 0);
    for (int i = 0; i < georgeCount; ++i) {
        cin >> tmp;
        // Want indexes from 0
        georgePath[i] = --tmp;
    }

    vector<map<int, edge>> paths(n, map<int, edge>());
    for (int i = 0; i < m; ++i) {
        cin >> A >> B >> L;
        // Want indexes from 0
        A--, B--;
        // Add path between intersections in both directions
        paths[A][B] = edge{A, B, L};
        paths[B][A] = edge{B, A, L};
    }

    int georgeTime = 0, newGeorgeTime;
    // For all george paths, add constraint on time it can be used
    for (int i = 0; i < georgeCount - 1; ++i) {
        int gA = georgePath[i], gB = georgePath[i + 1];
        newGeorgeTime = georgeTime + paths[gA][gB].weight;

        // Add in between which times the roads are blocked
        paths[gA][gB].blockStart = georgeTime;
        paths[gA][gB].blockEnd = newGeorgeTime;
        paths[gB][gA].blockStart = georgeTime;
        paths[gB][gA].blockEnd = newGeorgeTime;

        georgeTime = newGeorgeTime;
    }

    auto res = shortestPath(paths, lukS, lukE, lukasTimeDelay);

    cout << res[lukE] - lukasTimeDelay << '\n';

    cout << flush;

    return 0;
}