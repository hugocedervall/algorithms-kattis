/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-15
 * @PROBLEM: frogger
 *
 * Solution:
 *      A* with euclidean distance heuristic.
 *      Saves fastest path to every (x,y) position
 *      with a given amount of ticks shiftet (modulo width)
*/

#include <bits/stdc++.h>
#include <iostream>
#include <functional>

using namespace std;

struct gameState {
    int x{}, y{};
    int ticks = 0;
    double distGoal = 0;

    gameState(int x, int y, int ticks = 0, int goalX = 0, int goalY = 0) {
        this->x = x, this->y = y, this->ticks = ticks;
        // Bird distance to goal
        this->distGoal = sqrt(pow(abs(x - goalX), 2) + pow(abs(y - goalY), 2));
    }

    gameState() = default;


    bool operator<(const gameState &g) const {
        //if (ticks + distGoal == g.ticks + g.distGoal) {
        if (ticks == g.ticks) {
            if (x == g.x)
                return y > g.y;
            else
                return x > g.x;
        }
        return ticks + distGoal > g.ticks + g.distGoal;
    }

};

bool legalState(const vector<vector<char>> &gMap, const gameState &state) {
    // If out of bounds
    if (state.x >= gMap.size() || state.x < 0 || state.y >= gMap[state.x].size() || state.y < 0) return false;

    int width = gMap[state.x].size();
    int height = gMap.size();
    int moved;
    // Odd numbers are moving to right, even are moving to left
    if ((height - 1 - state.x) % 2 == 1) {
        // If moving right

        moved = (state.y - state.ticks) % width;
    } else {
        // If moving left
        moved = (state.y - (-state.ticks % width)) % width;
    }
    // c++ doesn't always make modulus positive
    if (moved < 0) moved += width;
    // Check within bounds and if not car
    return moved >= 0 && moved < width && gMap[state.x][moved] != 'X';
}

void
addState(vector<vector<char>> &gMap, priority_queue<gameState> &q, vector<vector<vector<int>>> &costs,
         gameState state) {
    if (legalState(gMap, state)) {
        int width = gMap[state.x].size();
        if (costs[state.x][state.y][state.ticks % width] > state.ticks) {
            q.push(state);
            costs[state.x][state.y][state.ticks % width] = state.ticks;
        }
    }
}

void
addNextStates(vector<vector<char>> &gMap, priority_queue<gameState> &q, vector<vector<vector<int>>> &costs,
              gameState &state,
              gameState &goal) {

    addState(gMap, q, costs, gameState{state.x, state.y + 1, state.ticks + 1, goal.x, goal.y});
    addState(gMap, q, costs, gameState{state.x, state.y - 1, state.ticks + 1, goal.x, goal.y});
    addState(gMap, q, costs, gameState{state.x + 1, state.y, state.ticks + 1, goal.x, goal.y});
    addState(gMap, q, costs, gameState{state.x - 1, state.y, state.ticks + 1, goal.x, goal.y});
    addState(gMap, q, costs, gameState{state.x, state.y, state.ticks + 1, goal.x, goal.y});

}


int solution(vector<vector<char>> &gMap, int maxRounds, gameState start, gameState goal) {
    // Lane closest to frog moves to right, then each other to right/left
    priority_queue<gameState> q;
    // Given a x,y cordinate with a given state, we only save the shortest
    vector<vector<vector<int>>> costs(gMap.size(),
                                      vector<vector<int>>(gMap[0].size(), vector<int>(gMap[0].size(), INT_MAX)));
    q.push(start);

    while (!q.empty()) {
        auto state = q.top();
        q.pop();

        if (state.ticks > maxRounds) return -1;

        if (gMap[state.x][state.y] == 'G')
            return state.ticks;

        // Move all possible directions from curr
        addNextStates(gMap, q, costs, state, goal);
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests, x, n, m;
    cin >> tests;

    for (int i = 0; i < tests; ++i) {
        cin >> x >> n >> m;
        gameState goalState{}, startState{};
        vector<vector<char>> gMap(n + 2, vector<char>(m));
        for (int xCord = 0; xCord < n + 2; ++xCord) {
            for (int yCord = 0; yCord < m; ++yCord) {
                cin >> gMap[xCord][yCord];
                if (gMap[xCord][yCord] == 'G') {
                    goalState = gameState{xCord, yCord};
                } else if (gMap[xCord][yCord] == 'F') {
                    startState = gameState{xCord, yCord};
                }
            }
        }
        int res = solution(gMap, x, startState, goalState);
        if (res == -1) cout << "The problem has no solution." << '\n';
        else cout << "The minimum number of turns is " << res << "." << '\n';

    }
    cout << flush;

    return 0;
}


