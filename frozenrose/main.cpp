/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-04
 * @PROBLEM: frozenrose
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Edge {
    int to, weight;
};

int solution(vector<vector<Edge>> &adj, vector<bool> &visitied, int s) {
    int count = 0;
    for (auto &e : adj[s]) {
        if (!visitied[e.to]) {
            visitied[e.to] = true;
            int newFound = solution(adj, visitied, e.to);
            count += newFound ? min(newFound, e.weight) : e.weight;
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c, u, v, w;
    while (cin >> n >> c) {
        // indexes from 0 to n-1
        c--;

        vector<vector<Edge>> adj(n, vector<Edge>());
        for (int i = 0; i < n - 1; ++i) {
            cin >> u >> v >> w;
            u--, v--;
            adj[u].push_back(Edge{v, w});

            adj[v].push_back(Edge{u, w});
        }
        vector<bool> vis(n, false);
        vis[c] = true;
        int res = solution(adj, vis, c);
        cout << res << endl;
    }
    return 0;
}