/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-11
 * @PROBLEM:
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

long long solution(int dist, vector<tuple<int, int>> stations) {
    // Remove all which are after final destination
    auto it = stations.begin();
    while (it != stations.end())
    {
        if (get<0>(*it) > dist) {
            it = stations.erase(it);
        }
        else {
            ++it;
        }
    }
    // in liters, always start with half tank
    int tank = 100;
    int spentMoney = 0;
    int cheapestReachableStation = 0;
    int currPos = 0;
    int currStation = -1;
    int nextPos = -1;
    while (currPos <= dist) {
        // If no tank, impossible to reach destination
        if (tank < 0) return -1;
        // If we can drive to final position
        if (currPos + tank - 100 >= dist) return spentMoney;

        if (nextPos != -1 && nextPos >= stations.size()) {
            return -1;
        }

        // Tank max if nothing else specified
        int tankHere = min(200 - tank, dist - currPos + 100 - tank);

        int currPrice = currStation != -1 ? get<1>(stations[currStation]) : INFINITY;
        cheapestReachableStation = currStation;

        // Find cheapest that can be reached
        for (int i = currStation + 1; i < stations.size(); ++i) {
            // If station can not be reached
            if (currPos + 200 < get<0>(stations[i])) break;
            // If station is cheaper
            if (get<1>(stations[i]) < currPrice) {
                cheapestReachableStation = i;
                // Distance to better station
                // Only want to berely reach station since its cheaper
                if (get<0>(stations[i]) - currPos < tank) {
                    tankHere = 0;
                } else {
                    tankHere = min(get<0>(stations[i]) - currPos - tank, dist - currPos + 100);
                }
                //currPrice = get<1>(stations[i]);
                break;
            }
        }

        // Current is cheapest within sight
        if (currStation == -1) {
            nextPos = currStation + 1;
        } else {
            // Tank amount at cheapest
            spentMoney += tankHere * get<1>(stations[currStation]);
            tank += tankHere;
            // If no cheaper found, buy as much as possible on current
            if (cheapestReachableStation == currStation) {
                // Drive to next station
                nextPos = currStation + 1;
            } else {
                // Drive to cheapest pos
                //nextPos = get<0>(stations[cheapestReachableStation]);
                nextPos = cheapestReachableStation;
                // Tank reduced by dist to next station
            }
        }
        if (nextPos < stations.size()) {
            tank -= (get<0>(stations[nextPos]) - currPos);
            currPos = get<0>(stations[nextPos]);
            currStation = nextPos;
        } /*else {
            currPos += tank;
            tank = 0;
        }*/
    }
    return spentMoney;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // truck consumes 1 liter / km
    // tank is 200 liters

    // at most 10000 km
    int distCity;
    cin >> distCity;
    int dist, cost;
    vector<tuple<int, int>> stations;
    while (cin >> dist >> cost) {
        stations.emplace_back(dist, cost);
    }

    long long res = solution(distCity, stations);
    if (res == -1) {
        cout << "Impossible" << endl;
    } else {
        cout << res << endl;
    }
    return 0;
}