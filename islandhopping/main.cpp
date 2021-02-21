/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-21
 * @PROBLEM: islandshopping
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Edge {
    pair<double, double> from, to;
    double distance;

    Edge(pair<double, double> from, pair<double, double> to) {
        this->from = from, this->to = to;
        // Euclidean distance between given nodes
        this->distance = sqrt(pow(from.first - to.first, 2) + pow(from.second - to.second, 2));
    }

    bool operator<(const Edge &e) const {
        if (distance == e.distance) return from > e.from;
        return distance > e.distance;
    }
};

/*
 * Prim's Minimul Spanning Tree algorithm
 */
double solution(vector<pair<double, double>> bridePos) {
    priority_queue<Edge> q;

    // Choose arbitary node to start with
    auto start = bridePos[0];

    // Path betweeen start and brideopenings
    for (auto b1 : bridePos) {
        q.push(Edge{start, b1});
    }

    map<pair<double, double>, bool> marked;
    double totalDistance = 0;
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();

        // Choose node only if outgoing is not already marked
        if (!marked[curr.to]) {
            marked[curr.to] = true;
            totalDistance += curr.distance;

            // For each connected which is not already marked
            for (auto &p : bridePos) {
                if (!marked[p]) {
                    q.push(Edge{curr.to, p});
                }
            }
        }
    }
    return totalDistance;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    double a, b;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> m;
        vector<pair<double, double>> bridgePos(m);
        for (int j = 0; j < m; ++j) {
            cin >> a >> b;
            bridgePos[j] = make_pair(a, b);
        }
        double res = solution(bridgePos);
        cout << setprecision(4) << res << '\n';
    }
    cout << flush;
    return 0;
}