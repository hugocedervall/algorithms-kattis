#include <iostream>
#include <cmath>
#include <tuple>

using namespace std;

int p, a, b, c, d, n;

double price(int k) {
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

int main() {
    cin >> p >> a >> b >> c >> d >> n;

    double diff = 0;
    double max = -1, min = -1;

    for (int i = 1; i <= n; ++i) {
        double currentPrice = price(i);
        if (currentPrice > max || max == -1) {
            max = currentPrice;
            min = currentPrice;
        }
        if (currentPrice < min || min == -1)
            min = currentPrice;

        if (max - min > diff)
            diff = max - min;

    }

    printf("%.9f\n", diff);
    return 0;
}
