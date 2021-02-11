/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-11
 * @PROBLEM: gold
 *
 * @SOLUTION:
 *      Flood fill algorithm with queue
*/

#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

struct node {
    char type;
    int x = 0;
    int y = 0;
    bool marked = false;

    vector<node> getValidNeighbours(vector<vector<node>> &gameMap) const {
        vector<node> neighbours;
        // If there is a sense of trap nearby, don't search neighbours
        if (draftSense(gameMap)) return neighbours;

        if (!gameMap[x][y - 1].isWall()) neighbours.push_back(gameMap[x][y - 1]);
        if (!gameMap[x][y + 1].isWall()) neighbours.push_back(gameMap[x][y + 1]);
        if (!gameMap[x - 1][y].isWall()) neighbours.push_back(gameMap[x - 1][y]);
        if (!gameMap[x + 1][y].isWall()) neighbours.push_back(gameMap[x + 1][y]);

        return neighbours;
    }

    bool isGold() const {
        return type == 'G';
    }

    bool isTrap() const {
        return type == 'T';
    }

    bool isWall() const {
        return type == '#';
    }

    bool draftSense(vector<vector<node>> &gameMap) const {
        return (gameMap[x][y - 1].isTrap() ||
                gameMap[x][y + 1].isTrap() ||
                gameMap[x - 1][y].isTrap() ||
                gameMap[x + 1][y].isTrap());
    }
};

int solution(vector<vector<node>> &gameMap, node player) {
    queue<node> q;
    q.push(player);
    int goldCount = 0;
    while (!q.empty()) {
        node curr = q.front();
        q.pop();
        if (gameMap[curr.x][curr.y].marked) continue;
        gameMap[curr.x][curr.y].marked = true;
        if (curr.isGold()) goldCount++;

        auto neighs = curr.getValidNeighbours(gameMap);
        for (auto &n : neighs) {
            if (!gameMap[n.x][n.y].marked) q.push(n);
        }
    }
    return goldCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int W, H;
    cin >> W >> H;
    char tmp;
    vector<vector<node>> gameMap(H, vector<node>(W));
    node playerNode;
    for (int x = 0; x < H; ++x) {
        for (int y = 0; y < W; ++y) {
            cin >> tmp;
            node tmpNode = node{tmp, x, y};
            gameMap[x][y] = tmpNode;
            if (tmp == 'P') {
                playerNode = tmpNode;
            }
        }
    }

    int res = solution(gameMap, playerNode);
    cout << res << endl;

    return 0;
}