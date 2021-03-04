/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-03-04
 * @PROBLEM: brexit
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Country {
    bool leftUnion;
    int remainNeigh;
    vector<int> neigh;

    Country() {
        remainNeigh = 0;
        leftUnion = false;
        neigh = vector<int>();
    }
};


bool leftUnion(vector<Country> &countries, int start, int end) {
    // Countries to process
    queue<int> q;

    // Start with first leaving union
    countries[start].leftUnion = true;
    // reduce neighbours for union
    for (int i = 0; i < countries[start].neigh.size(); ++i) {
        countries[countries[start].neigh[i]].remainNeigh--;
        q.push(countries[start].neigh[i]);
    }

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        // if left, then already processed
        if (countries[curr].leftUnion) continue;

        // if at least half of neigh left, this country also leaves
        if (countries[curr].neigh.size() / 2 >= countries[curr].remainNeigh) {
            countries[curr].leftUnion = true;
            // Decrease neighbour for all neighs
            for (int n : countries[curr].neigh) {
                countries[n].remainNeigh--;
                q.push(n);

            }
        }
    }
    return countries[end].leftUnion;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int c, p, x, l, a, b;
    cin >> c >> p >> x >> l;

    // want node 0 to n-1 instead
    x--, l--;

    vector<Country> countries(c);

    for (int i = 0; i < p; ++i) {
        cin >> a >> b;
        // want node 0 to n-1 instead
        a--, b--;

        countries[a].neigh.push_back(b);
        countries[b].neigh.push_back(a);

        countries[a].remainNeigh++;
        countries[b].remainNeigh++;
    }

    bool res = leftUnion(countries, l, x);

    cout << (res ? "leave" : "stay") << endl;

    return 0;
}