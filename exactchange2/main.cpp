#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

// Max cost of purchase
int MAX_PRICE = 10000;

void algo(const int coins[], int differentCoins, int purchasePrice) {
    int table[MAX_PRICE + 1];

    // 0 coins for cost 0
    table[0] = 0;

    // Unknown coins for rest of costs
    for (int i = 1; i <= MAX_PRICE; i++)
        table[i] = INT_MAX;

    // Find minimum amount of coins for all possible prices
    for (int i = 0; i < differentCoins; ++i) {
        int coin = coins[i];

        for (int price = MAX_PRICE - coin; price >= 0; price--) {
            // If we can make price with fewer coins
            table[price + coin] = min(table[price + coin], table[price] == INT_MAX ? table[price] : table[price] + 1);
        }
    }

    // Find smallest number abone given purchasePrice purchasePrice
    for (int i = purchasePrice; i < MAX_PRICE + 1; ++i) {
        if (table[i] < INT_MAX) {
            cout << i << " " << table[i] << endl;
            break;
        }
    }
}


int main() {
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; ++i) {
        int price;
        int n;
        cin >> price >> n;

        int change[n];
        for (int j = 0; j < n; ++j) {
            int bill;
            cin >> bill;
            change[j] = bill;
        }
        sort(change, change + n);
        algo(change, n, price);
    }

    return 0;
}
