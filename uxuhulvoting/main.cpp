/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-09
 * @PROBLEM: uxuhulvoting
 *
*/

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>

using namespace std;

bitset<3> solution(vector<vector<int>> &wishes, vector<vector<int>> &states, int currPriest, int state) {
    // All priest have voted
    if (currPriest >= wishes.size()) return state;
    // If already computed
    if(states[currPriest][state] != -1) return states[currPriest][state];
    // Best found state for current priest, 0 is the best
    bitset<3> best;
    bool bestSet = false;
    // Three possible outcomes from flipping a stone, given a state
    for (int i = 0; i < 3; ++i) {
        bitset<3> currState = state;
        currState.flip(i);

        // What would this current state result in for last state
        bitset<3> res = solution(wishes, states, currPriest + 1, int(currState.to_ulong()));

        // If current state is more wanted for curr priest
        if (!bestSet || wishes[currPriest][int(res.to_ulong())] < wishes[currPriest][int(best.to_ulong())]) {
            best = res.to_ulong();
            bestSet = true;
        }
    }
    states[currPriest][state] = best.to_ulong();

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, tmp;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> m;
        vector<vector<int>> wishes(m, vector<int>(8, 0));
        for (int wizNr = 0; wizNr < m; ++wizNr) {
            for (int outcome = 0; outcome < 8; ++outcome) {
                cin >> tmp;
                // Save 0...7 instead of 1...8
                wishes[wizNr][outcome] = tmp - 1;
            }
        }
        vector<vector<int>> states(m, vector<int>(8, -1));
        bitset<3> res = solution(wishes, states, 0, 0);
        string vote = res.to_string();
        replace(vote.begin(), vote.end(),'0', 'N');
        replace(vote.begin(), vote.end(),'1', 'Y');
        cout << vote << '\n';
    }
    cout << flush;

    return 0;
}