/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-01
 * @PROBLEM: hidingplaces
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int CHESS_SIZE = 8;

// Returns valid knight moves
vector<pair<int, int>> validKnightMoves(pair<int, int> pos) {
    vector<int> xMoves = {2, 1, -1, -2, -2, -1, 1, 2};
    vector<int> yMoves = {1, 2, 2, 1, -1, -2, -2, -1};

    vector<pair<int, int>> validMoves;
    for (int i = 0; i < xMoves.size(); ++i) {
        int newX = pos.first + xMoves[i];
        int newY = pos.second + yMoves[i];
        if (newX >= 0 && newY >= 0 &&
            newX < CHESS_SIZE && newY < CHESS_SIZE)
            validMoves.emplace_back(newX, newY);
    }
    return validMoves;
}

vector<vector<int>> dijkstra(pair<int, int> start) {
    vector<vector<int>> gameMap(CHESS_SIZE, vector<int>(CHESS_SIZE, INT_MAX));

    auto cmp = [](const pair<int, pair<int, int>> a, const pair<int, pair<int, int>> b) {
        if (a.first == b.first) return a.first > b.first;
        return a.first > b.first;
    };
    // Priority queue of cost and positions
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(cmp)> q(cmp);

    // Cost to itself is 0
    q.push({0, start});
    gameMap[start.first][start.second] = 0;

    while (!q.empty()) {
        auto curr = q.top();
        int currCost = curr.first;
        auto currPos = curr.second;
        q.pop();

        // For each valid move that is cheaper than found
        for (auto &m : validKnightMoves(currPos)) {
            if (currCost + 1 < gameMap[m.first][m.second]) {
                gameMap[m.first][m.second] = currCost + 1;
                q.push({currCost + 1, m});
            }
        }

    }

    return gameMap;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int n;
    cin >> n;

    string input;
    while (n--) {
        cin >> input;
        int y = input[1] - '1';
        int x = input[0] - 'a';
        vector<vector<int>> dist = dijkstra({x, y});
        int maxFound = 0;

        for (int i = 0; i < dist.size(); ++i) {
            for (int j = 0; j < dist.size(); ++j) {
                if (dist[i][j] > maxFound) maxFound = dist[i][j];
            }
        }

        vector<string> moves;
        for (int i = dist.size() - 1; i >= 0; --i) {
            for (int j = 0; j < dist.size(); j++) {
                if (dist[j][i] == maxFound) {
                    string pos = "";
                    pos += char(j) + 'a';
                    pos += char(i) + '1';
                    moves.push_back(pos);
                }
            }
        }
        // Print results
        cout << maxFound;
        for (auto &m: moves) cout << " " << m;
        cout << '\n';
    }

    cout << flush;


    return 0;
}