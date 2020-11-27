#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// O(len(d))
unsigned int algo(long d) {
    unsigned int results = 0;
    unsigned int i = 1;

    while (true) {
        unsigned int b = int(d / i);
        unsigned int c = d % i;

        unsigned int a = int(b / 10);
        b = b % 10;

        if (a == 0) {
            return results;
        }

        if (b == 0) {
            results += (a - 1) * i + c + 1;
        } else {
            results += a * i;
        }
        i *= 10;
    }
}


int main() {
    unsigned int m, n;

    while (cin >> m >> n && !(m == -1 && n == -1)) {
        unsigned int nn = algo(n);
        unsigned int mm = algo(m);

        // If 0's in m, add occurrences to total
        string mStr = to_string(m);
        int zeroCount = count(mStr.begin(), mStr.end(), '0');
        if (zeroCount > 0) nn += zeroCount;

        cout << nn - mm << endl;
    }


    return 0;
}
