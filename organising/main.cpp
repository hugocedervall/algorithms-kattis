/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-05-09
 * @PROBLEM: organising
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const double EPS = 1e-9;

typedef long double ld;

/**
 * Applying Gauss mathod to the matrix, which will result in a diagonal matrix. The
 * determinant of this matrix is simply the product of the diagonal.
 */
double determinant(vector<vector<ld>> matrix, int n) {
    // Gauss method
    for (int i = 0; i < n; ++i) {
        // No solution if one node has no adj
        if (abs(matrix[i][i]) < EPS) return 0;
        for (int j = i + 1; j < n; ++j)
            matrix[i][j] /= matrix[i][i];
        for (int j = 0; j < n; ++j)
            if (j != i && abs(matrix[j][i]) > EPS)
                for (int k = i + 1; k < n; ++k)
                    matrix[j][k] -= matrix[i][k] * matrix[j][i];
    }

    // Determinant is product of matrix diagonal after applying gauss method
    double det = 1;
    for (int i = 0; i < n; ++i)
        det *= matrix[i][i];

    return abs(det);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, m, a, b;
    while (cin >> n >> k >> m) {
        vector<vector<ld>> lap(n, vector<ld>(n, 0));
        vector<vector<bool>> cooperate(n, vector<bool>(n, true));

        // nodes which can not cooperate
        for (int _ = 0; _ < k; ++_) {
            cin >> a >> b;
            // 0 to n-1 instead of 1 to n
            a--, b--;
            cooperate[a][b] = false, cooperate[b][a] = false;
        }

        // Laplacian matrix for all nodes but those who can not cooperate
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                // only if nodes can cooperate
                if (cooperate[i][j]) {
                    // Increase degree of nodes
                    lap[i][i]++;
                    lap[j][j]++;
                    // non-diagnonals to -1
                    lap[i][j] = -1, lap[j][i] = -1;
                }

        /* Kirchhoff's matrix tree theorem says that number of spanning tree in graph
         * is equal to the deteminant of an laplacian matrix from the graph. Ignore last
         * row and column, since one node is always top of the organisation */
        long long res = determinant(lap, n - 1);
        cout << res << '\n';
    }

    cout << flush;

    return 0;
}
