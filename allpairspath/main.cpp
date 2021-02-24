/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-24
 * @PROBLEM: allpairspath
 *      Find the shortest distance between all nodes in a network. Edges
 *      between nodes can have negative weights, so negative cycles are
 *      possible. This is handled such that all paths which are reachable
 *      from a negative cycle are labeled with -inf. Paths which are not
 *      reachable at all are labeled with inf.
 *
 * @COMPLEXITIES:
 *      O(n^3), where n = amount of nodes.
 *          This is easily motivated by the nested for loops.
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
ll llMax = LLONG_MAX;

/**
 * Find the shortest path between all nodes in a network. As negative weights
 * are possible, there can exist negative cycles. All paths reachable from
 * negative cycles are labeled as -inf. Paths which are not reachable at all
 * are labelled with inf.
 *
 * @param d results will be updated in this variable. Consists of path costs
 * between all nodes. Paths which are not reachable are labelled with inf, and
 * paths which are reachable by negative cycles are labelled with -inf.
 */
void shortestPathAllPairs(vector<vector<ll>> &d) {
    // Find shortest paths
    for (ll k = 0; k < d.size(); ++k)
        for (ll i = 0; i < d.size(); ++i)
            for (ll j = 0; j < d.size(); ++j)
                if (d[i][k] < llMax && d[k][j] < llMax)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);


    // Find negative cycles
    for (ll k = 0; k < d.size(); ++k)
        for (ll i = 0; i < d.size(); ++i)
            for (ll j = 0; j < d.size(); ++j)
                // If some path through node k where k is reachable from
                // negative cycle, the path out of k is also reachable
                // from a negative cycle.
                if (d[k][k] < 0 && d[i][k] != llMax && d[k][j] != llMax)
                    d[i][j] = -llMax;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, q, u, v, w, qU, qV;
    while (cin >> n >> m >> q) {
        if (n == 0 & m == 0 && q == 0) break;

        vector<vector<ll>> d(n, vector<ll>(n, llMax));

        // Distance for all nodes to themselves set to 0
        for (ll i = 0; i < n; ++i)
            d[i][i] = 0;

        for (ll i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            // In case of multiple edges between nodes, use smallest
            d[u][v] = min(w, d[u][v]);
        }

        shortestPathAllPairs(d);

        for (ll i = 0; i < q; ++i) {
            cin >> qU >> qV;
            if (d[qU][qV] == -llMax) {
                cout << "-Infinity" << '\n';
            } else if (d[qU][qV] == llMax) {
                cout << "Impossible" << '\n';
            } else {
                cout << d[qU][qV] << '\n';
            }
        }
        cout << '\n';
    }
    cout << flush;

    return 0;
}