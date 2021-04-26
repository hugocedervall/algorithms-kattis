/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-26
 * @PROBLEM: jughard
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

bool solution(int a, int b, int d){
    int gcd = __gcd(a,b);
    return d % gcd == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int t,a,b,d;
    cin >> t;
    while(t--){
        cin >> a >> b >>d;
        bool res = solution(a,b,d);
        cout << (res ? "Yes" : "No") << '\n';
    }
    cout << flush;

    return 0;
}