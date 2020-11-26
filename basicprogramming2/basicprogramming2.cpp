#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "map"

using namespace std;

// O(N)
bool action1(vector<long> const &data) {
    // Create set from vector so no repetitions later
    unordered_set<long> dataSet;
    for (const int x: data) {
        dataSet.insert(x);
    }

    // If both x and y=num-x in set, we have solution x+y=num
    int searchedSum = 7777;
    for (long x : dataSet) {
        if (dataSet.find(x) != dataSet.end() && dataSet.find(searchedSum-x) != dataSet.end()){
            return true;
        }
    }

    return false;
}

// O(N^2)
bool action2(vector<long> const &data) {
    for (int i = 0; i < data.size() - 1; ++i) {
        for (int j = i + 1; j < data.size(); ++j) {
            if (data[i] == data[j]) return false;
        }
    }
    return true;
}


// O(N)
int action3(double N, vector<long> const &data) {
    map<int, int> m;

    for (int i = 0; i < data.size(); ++i) {
        // If first time searching for occurrences for number
        m[data[i]] += 1;
    }

    // See if amount of occurances over threshold
    for (auto const &x : m) {
        if (x.second > N / 2) return x.first;
    }

    return -1;
}

// O(N log N)
vector<long> action4(vector<long> data) {
    size_t size = data.size();

    sort(data.begin(), data.end());

    vector<long> means;

    if (size % 2 == 0)
        means.push_back(data[size / 2 - 1]);
    means.push_back(data[size / 2]);

    return means;
}

// O(N log N)
vector<long> action5(vector<long> data) {
    vector<long> newData;

    // Filter out numbers not in the range [100,..,999]
    copy_if(data.begin(), data.end(), back_inserter(newData), [](long i) { return i >= 100 && i <= 999; });

    sort(newData.begin(), newData.end());

    return newData;
}

// Algorithm
int bpg2(int N, int t, vector<long> data) {

    switch (t) {
        case 1: {
            if (action1(data)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
            break;
        }
        case 2: {
            if (action2(data)) {
                cout << "Unique" << endl;
            } else {
                cout << "Contains duplicate" << endl;
            }
            break;
        }
        case 3: {
            cout << action3(N, data) << endl;
            break;
        }
        case 4: {
            vector<long> means = action4(data);
            if (means.size() == 1) {
                cout << means[0] << endl;
            } else {
                cout << means[0] << " " << means[1] << endl;
            }
            break;
        }
        case 5: {
            vector<long> filteredData = action5(data);
            for (auto it = filteredData.begin(); it != filteredData.end(); it++) {
                if (next(it) == filteredData.end()) {
                    cout << *it;
                } else {
                    cout << *it << " ";
                }
            }
            cout << endl;
        }
    }
    return 0;
}


int main() {
    // Read initial int inputs
    int N, t;
    cin >> N >> t;

    // Read vector input
    vector<long> data(N);
    for (int i = 0; i < N; ++i) {
        cin >> data[i];
    }

    bpg2(N, t, data);

    return 0;
}

