/**
 *
 * PROBLEM: aspenavenue
 * AUTHOR: Hugo Cedervall
 *
 * Comments:
 *      * Output relative error of at most 1e-6
 *
 */

#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Calculates the required moving distance for a pair of trees in order
 * to get them side by side.
 *
 * @return
 */
double distanceBetween(double posA, double posB, int width) {
    double height = fabs(posA - posB);
    double distance = sqrt(pow(height, 2) + pow(width, 2));
    return distance;
}

double distanceBetween(double posA, double posB) {
    return fabs(posA - posB);
}

double solution3(int N, int L, int W, vector<int> positions) {
    // Get trees in order
    sort(positions.begin(), positions.end());

    // Amount of trees on each side
    int n = N / 2;

    double stepSize = (double) L / (n - 1);

    // Assigned x trees on left side
    // Assigned y trees on right side
    double distances[n + 1][n + 1];
    for (int x = 0; x < n + 1; ++x)
        for (int y = 0; y < n + 1; ++y)
            distances[x][y] = INFINITY;
    distances[0][0] = 0;

    for (int left = 0; left < n + 1; ++left) {
        for (int right = 0; right < n + 1; ++right) {
            int pos = positions[left + right];
            double curr = distances[left][right];
            double currBestDist = distances[left][right];
            double goalYPos, newDist;


            if (left < n) {
                // if not seen height previously
                currBestDist = distances[left + 1][right];
                goalYPos = stepSize * left;
                newDist = distanceBetween(goalYPos, pos) + curr;
                if (currBestDist < INT_MAX) {
                    // If better solution found
                    if (newDist < currBestDist) {
                        distances[left + 1][right] = newDist;
                    }
                } else {
                    distances[left + 1][right] = newDist;
                }
            }


            if (right < n) {
                currBestDist = distances[left][right + 1];
                goalYPos = stepSize * right;
                newDist = distanceBetween(goalYPos, pos, W) + curr;
                // If not seen config before
                if (currBestDist < INT_MAX) {
                    // If better solution found
                    if (newDist < currBestDist) {
                        distances[left][right + 1] = newDist;
                    }
                } else {
                    distances[left][right + 1] = newDist;
                }
            }


        }
    }
    return distances[n][n];
}


int main() {
    // Read variables from input
    int N, L, W;
    while (cin >> N) {
        cin >> L >> W;

        vector<int> positions;

        int tmp;
        for (int i = 0; i < N; ++i) {
            cin >> tmp;
            positions.push_back(tmp);
        }

        double output = solution3(N, L, W, positions);

        //cout << output << endl;
        printf("%.10f\n", output);
    }
    return 0;
}


