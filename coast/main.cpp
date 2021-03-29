/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-29
 * @PROBLEM: coast
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct node {
    char type = '0';
    int x = 0;
    int y = 0;
    bool marked = false;

    vector<node> getValidNeighbours(vector<vector<node>> &gameMap) const {
        vector<node> neighbours;
        // If there is a sense of trap nearby, don't search neighbours
        //if (draftSense(gameMap)) return neighbours;

        if (y > 0 && gameMap[x][y - 1].validMove()) neighbours.push_back(gameMap[x][y - 1]);
        if (y < gameMap[0].size() - 1 && gameMap[x][y + 1].validMove()) neighbours.push_back(gameMap[x][y + 1]);
        if (x > 0 && gameMap[x - 1][y].validMove()) neighbours.push_back(gameMap[x - 1][y]);
        if (x < gameMap.size() - 1 && gameMap[x + 1][y].validMove()) neighbours.push_back(gameMap[x + 1][y]);

        return neighbours;
    }

    bool isLand() const {
        return type == '1';
    }

    bool isWater() const {
        return type == '0';
    }

    bool markedWater() const{
        return this->isWater() && this->marked;
    }

    bool validMove() const {
        return this->isWater() && !this->marked;
    }


};

int solution(vector<vector<node>> &gameMap, node player) {
    queue<node> q;
    q.push(player);
    while (!q.empty()) {
        node curr = q.front();
        q.pop();

        //if(gameMap[curr.x][curr.y].type == '1') continue;
        if (gameMap[curr.x][curr.y].marked) continue;

        gameMap[curr.x][curr.y].marked = true;

        auto neighs = curr.getValidNeighbours(gameMap);
        for (auto &n : neighs) {
            if (!gameMap[n.x][n.y].marked) q.push(n);
        }
    }

    // Count amount of edges to water
    int totalDistance = 0;
    for (int x = 0; x < gameMap.size(); ++x) {
        for (int y = 0; y < gameMap[0].size(); ++y) {
            if (gameMap[x][y].isLand()) {
                // The tiles around
                int waterAround = 0;
                if (y > 0 && gameMap[x][y - 1].markedWater()) waterAround++;
                if (y < gameMap[0].size() - 1 && gameMap[x][y + 1].markedWater()) waterAround++;
                if (x > 0 && gameMap[x - 1][y].markedWater()) waterAround++;
                if (x < gameMap.size() - 1 && gameMap[x + 1][y].markedWater()) waterAround++;

                // not if alone island
                //if (waterAround < 4) totalDistance += waterAround;
                totalDistance += waterAround;
            }
        }
    }


    /*for (int i = 0; i < gameMap.size(); ++i) {
        for (int j = 0; j < gameMap[0].size(); ++j) {
            cout << gameMap[i][j].marked;
        }
        cout << endl;
    }*/
    return totalDistance;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int W, H;
    cin >> H >> W;
    char tmp;
    // add border around with water
    vector<vector<node>> gameMap(H + 2, vector<node>(W + 2));
    for (int x = 0; x <= H + 1; ++x) {
        for (int y = 0; y <= W + 1; ++y) {
            node tmpNode = node{'0', x, y};
            gameMap[x][y] = tmpNode;
        }
    }

    node playerNode = node{'0', 0, 0};
    for (int x = 1; x <= H; ++x) {
        for (int y = 1; y <= W; ++y) {
            cin >> tmp;
            node tmpNode = node{tmp, x, y};
            gameMap[x][y] = tmpNode;
        }
    }

    int res = solution(gameMap, playerNode);
    cout << res << endl;

    return 0;
}