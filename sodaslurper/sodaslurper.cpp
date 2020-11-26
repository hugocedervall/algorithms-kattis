#include <iostream>

using namespace std;

int sodaSlurper(int e, int f, int c) {
    int drunken = 0, empty_bottles = e + f;

    while (empty_bottles >= c) {
        int bought_bottles = empty_bottles / c;

        // Amount of total drunken bottles
        drunken += bought_bottles;

        // Amount of empty bottles remaining after buying new
        empty_bottles = empty_bottles % c;

        // After drinking newly bought bottles
        empty_bottles += bought_bottles;
    };
    
    return drunken;
}

int main() {
    int e, f, c;
    cin >> e >> f >> c;

    cout << sodaSlurper(e, f, c) << endl;

    return 0;
}

