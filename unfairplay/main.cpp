/*
 * @AUTHOR: Hugo Cederrvall
 * @DATE: 2021-03-28
 * @PROBLEM: unfairplay
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

    int n, m;
    while (cin >> n && n != -1 && cin >> m) {

        vector<int> points(n, 0);
        for (int i = 0; i < n; ++i)
            cin >> points[i];

        int v = n + m + 1;
        int source = 0, sink = v;

        int a, b;
        vector<pair<int, int>> matches(m);
        for (int i = 0; i < m; ++i) {
            cin >> a >> b;
            matches[i] = {a, b};
        }


        vector<vector<int>> adj(v + 1, vector<int>());
        // u, v to remaining and used flow
        vector<vector<cap>> caps(v + 1, vector<cap>(v + 1));

        // First [1...m] nodes represents the matches
        // Following [m+1...m+n] nodes represents the teams
        // Node 0 is src, and node n+m+1 represents sink

        int nodeNr;
        for (int i = 0; i < matches.size(); ++i) {
            pair<int, int> match = matches[i];

            // The maximum amount of points our desired team can get
            // if they win every match
            if (match.first == n || match.second == n) {
                points[n-1] += 2;
                continue;
            }

            int a = match.first + m + 1, b = match.second + m + 1;

            // The node id is 1 more than index
            nodeNr = i + 1;

            // Match has 2 points to give
            adj[source].push_back(nodeNr);
            // TODO: += 2 insead of just 2
            caps[source][nodeNr] = cap{2, 0};

            // Add path from match to the teams competing
            adj[nodeNr].push_back(a);
            adj[match.first].push_back(nodeNr);
            caps[nodeNr][match.first] = cap{INT_MAX, 0};

            adj[nodeNr].push_back(b);
            adj[match.second].push_back(nodeNr);
            caps[nodeNr][match.second] = cap{INT_MAX, 0};
        }

        // Add path from all teams to sink, with initial used
        // capacity as their initial scores
        for (int i = 0; i < n; ++i) {
            int nodeNr = i + m + 1;

            adj[nodeNr].push_back(sink);
            adj[sink].push_back(nodeNr);
            // We must only send so much that no team gets more points
            // than our desired winner
            caps[nodeNr][sink] = cap{points[n-1] - points[i] - 1, 0};
        }


        int flow = maxflow(source, sink, adj, caps);
        cout << flow << endl;

        // output
        // victory of the first team by 0, a draw by 1, and the victory of the second team by 2
    }


    return 0;
}