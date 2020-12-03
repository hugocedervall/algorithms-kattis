#include <iostream>
#include <cmath>

using namespace std;

int MIN_YEAR = 1960;

// How can this be done better ?
int LOOKUP_N[] = {3, 5, 8, 12, 20, 34, 57, 98, 170, 300, 536, 966, 1754,
                  3210, 5910, 10944, 20366, 38064, 71421, 134480, 254016};

int algo(int year) {
    // Remove last digit (only care about every 10 year)
    int year_rounded = int(year / 10) * 10;
    int years = year_rounded - MIN_YEAR;
    int bits = years / 10;

    // amount of available bits at given year
    int bitsAmount = 4 * pow(2, bits);

    return LOOKUP_N[bits];
}

int main() {
    int year;
    while (cin >> year && year != 0) {
        cout << algo(year) << endl;
    }
    return 0;
}
