/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-11
 * @PROBLEM: borg
 *
*/

#include <bits/stdc++.h>
#include <iostream>
#include <map>

using namespace std;

struct node {
    int x{}, y{};
    char type{};
    int cost = INT_MAX;
    bool marked = false;
    pair<int, int> from;

    bool operator<(const node &n) const {
        if (cost == n.cost) return x < n.x;
        return cost < n.cost;
    }

    // Returns neighbours to current node which are not wall
    vector<node> getNeighs(vector<vector<node>> &map) {
        vector<node> neigh;
        if (map[x][y + 1].type != '#') neigh.push_back(map[x][y + 1]);
        if (map[x][y - 1].type != '#') neigh.push_back(map[x][y - 1]);
        if (map[x + 1][y].type != '#') neigh.push_back(map[x + 1][y]);
        if (map[x - 1][y].type != '#') neigh.push_back(map[x - 1][y]);
        return neigh;
    }
};

// Edge between nodes, used to find minimum spanning tree
struct edge {
    pair<int, int> node1, node2;
    int cost = 0;

    bool operator<(const edge &e) const {
        if (cost == e.cost) return node1.first > e.node1.first;
        return cost > e.cost;
    }
};

/**
 *
 * Dijkstras algorithm to find smallest path between @param startNode
 * and all nodes of type S (start) or A (alien)
 *
 * @param map 2d map over all nodes
 * @param edges all minimal costs edges between aliens and start point
 * @param curr search path to other nodes from curr
 */
void dijkstra(vector<vector<node>> &map, vector<edge> &edges, node startNode) {
    priority_queue<node> q;
    vector<vector<int>> costs(map.size(), vector<int>(map[0].size(), INT_MAX));
    costs[startNode.x][startNode.y] = 0;
    q.push(map[startNode.x][startNode.y]);
    while (!q.empty()) {
        auto curr = q.top();
        int currCost = costs[curr.x][curr.y];
        q.pop();

        // If not startnode, add edge between startnode and found Alien/start
        if (!(startNode.x == curr.x && startNode.y == curr.y) &&
            (curr.type == 'S' || curr.type == 'A')) {
            edges.push_back(edge{make_pair(startNode.x, startNode.y),
                                 make_pair(curr.x, curr.y),
                                 currCost});
        }

        // For all neighbours
        for (auto &neigh : curr.getNeighs(map)) {
            // If path is cheaper from current node
            if (currCost + 1 < costs[neigh.x][neigh.y]) {
                costs[neigh.x][neigh.y] = currCost + 1;
                //map[neigh.x][neigh.y].from = make_pair(curr.x, curr.y);
                q.push(map[neigh.x][neigh.y]);
            }
        }
    }
}


int solution(vector<vector<node>> &map) {
    vector<edge> edges;

    // Amount of S and A in map
    int total_marked = 0;

    // Dijkstras Algorithm
    // for every S (start) and A (alien) nodes
    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[0].size(); ++y) {
            if (map[x][y].type == 'S' || map[x][y].type == 'A') {
                // Find path costs from curr to all S (start) and A (aliens)
                dijkstra(map, edges, map[x][y]);
                total_marked++;
            }
        }
    }

    // No cost
    if (edges.empty()) return 0;

    // Prim’s Minimum Spanning Tree (MST) Algorithm
    // This could be done much faster by mapping each node its edges,
    // right now all edges all looped through each time

    // Used to always first add the cheapest edges
    priority_queue<edge> edgeQ;

    // Push all edges connected to arbitary node
    pair<int, int> arbNode = edges[0].node1;
    for (auto &e: edges) {
        if (e.node1.first == arbNode.first && e.node1.second == arbNode.second) {
            edgeQ.push(e);
        }
    }

    int total_cost = 0;
    vector<vector<bool>> marked(map.size(), vector<bool>(map[0].size(), false));
    marked[edgeQ.top().node1.first][edgeQ.top().node1.second] = true;
    while (!edgeQ.empty() && total_marked > 0) {
        auto curr = edgeQ.top();
        edgeQ.pop();

        // Chose edge only if outgoing node is not already marked
        // This is guaranteed to be the cheapest
        if (!marked[curr.node2.first][curr.node2.second]) {
            marked[curr.node2.first][curr.node2.second] = true;
            total_cost += curr.cost;

            // For each connected node, if not marked, add edge to queue
            for (auto &e: edges) {
                if (e.node1.first == curr.node2.first && e.node1.second == curr.node2.second &&
                    !marked[e.node2.first][e.node2.second]) {
                    edgeQ.push(e);
                }
            }
        }
    }

    return total_cost;
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(NULL);

    int n;
    cin >> n;
    int W, H;
    char tmp;
    string line;

    for (int i = 0; i < n; ++i) {
        cin >> W >> H;
        cin.ignore();
        vector<vector<node>> map(H, vector<node>(W));
        for (int x = 0; x < H; ++x) {
            getline(cin, line);
            for (int y = 0; y < W; ++y) {
                tmp = line[y];
                node tmpNode = node{x, y, tmp};
                map[x][y] = tmpNode;
            }
        }

        int res = solution(map);

        cout << res << '\n';
    }
    cout << flush;

    return 0;
}