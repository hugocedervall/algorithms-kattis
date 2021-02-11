/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-11
 * @PROBLEM: 
*/

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;


long long solution(vector<long long> costs){
    sort(costs.begin(), costs.end(), greater<>());
    long long discout = 0;
    for (int i = 0; i < costs.size(); i+=3) {
        if(i+2 < costs.size()){
            discout += costs[i+2];
        }
    }
    return discout;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    long long n;
    cin >> n;
    vector<long long> costs(n);
    for (int i = 0; i < n; ++i) {
        cin >> costs[i];
    }

    long long res = solution(costs);
    cout << res << endl;

    return 0;
}