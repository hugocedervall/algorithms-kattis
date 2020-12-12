#include <iostream>
#include <set>

using namespace std;


int main() {
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; ++i) {
        int W;
        cin >> W;

        set<int> diffs;
        for (int j = 0; j < W; ++j) {
            int a, b;
            cin >> a >> b;
            diffs.insert(abs(a - b));
        }
        if (diffs.size() > 1) cout << "no" << endl;
        else cout << "yes" << endl;

        if (i != cases-1) cout << endl;
    }

    return 0;
}
