/**
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-25
 * @PROBLEM: caching
 *
 * Complexity:
 *      O(n * log n)
 */

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(int c, int a, int reads[]) {
    // Used to store elements. capacity c
    set<int> cache;

    // Input indexes for element
    unordered_map<int, set<int>> order;

    // Sort based on which occurs the furthest away
    auto cmp = [](pair<int, int> a, pair<int, int> b) {
        if (get<1>(a) == get<1>(b)) return get<0>(a) > get<0>(b);
        return get<1>(a) > get<1>(b);
    };
    set<pair<int, int>, decltype(cmp)> nextOccur(cmp);

    // Used to have direct mapping from element to pair which can then be found in nextOccur
    unordered_map<int, pair<int, int>> nextOccLookup;

    // Which indexes each elem comes at
    for (int i = 0; i < a; ++i) {
        order[reads[i]].insert(i);
    }

    int cacheReads = 0;
    for (int i = 0; i < a; ++i) {
        order[reads[i]].erase(order[reads[i]].begin());
        // No cached element
        if (cache.find(reads[i]) == cache.end()) {
            // If cache is full
            if (cache.size() == c) {
                // Remove elem with longest distance to next occurance
                auto it = nextOccur.begin();
                pair<int, int> front = *it;
                nextOccur.erase(it);
                nextOccLookup.erase(get<0>(front));
                cache.erase(get<0>(front));
            }

            // Insert location for next occurance of element
            int nextI;
            if (order[reads[i]].empty())
                nextI = INT_MAX;
            else
                nextI = *order[reads[i]].begin();

            // Insert next occurance of number
            auto p = make_pair(reads[i], nextI);
            nextOccur.insert(p);
            nextOccLookup[reads[i]] = p;
            cache.insert(reads[i]);
            cacheReads++;
        }
            // Cached element
        else {
            // Find next position of cached element
            auto res = nextOccLookup.find(reads[i]);
            if (res != nextOccLookup.end()) {
                nextOccur.erase(nextOccur.find(res->second));

                int nextI;
                if (order[reads[i]].empty())
                    nextI = INT_MAX;
                else
                    nextI = *order[reads[i]].begin();

                // Insert next occurance of number
                auto p = make_pair(reads[i], nextI);
                nextOccur.insert(p);
                nextOccLookup[reads[i]] = p;
            }
        }
    }
    return cacheReads;
}

int main() {
    int c, n, a;
    cin >> c >> n >> a;

    int reads[a];
    for (int i = 0; i < a; ++i)
        cin >> reads[i];

    int res = solution(c, a, reads);
    cout << res << endl;

    return 0;
}