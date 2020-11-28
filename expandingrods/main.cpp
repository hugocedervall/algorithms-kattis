#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

double binSearch(double left, double right, double LL, double L) {

    // Force runs to get precision
    int threshold = 40;
    int counter = 0;

    double foundDistance = -1;

    // While left and right pointers dont cross
    while (left <= right && counter <= threshold) {
        double theta = (left + right) / 2;

        /*
         * arLen = (theta / 2*pi) * 2*pi*r ->
         * r = arcLen / ((theta /2*pi)*(2*pi)= ->
         * r = arcLen / theta
        */
        double r = LL / theta;

        double lHat = 2.0 * sin(theta / 2.0) * r;

        // Solution found
        foundDistance =  (r - cos(theta / 2) * r);


        if (lHat > L) {
            left = theta;
        } else {
            right = theta;
        }
        counter ++;
    }
    return foundDistance;
}



int main() {
    const double pi = acos(-1);

    double L, n, C;
    while (cin >> L >> n >> C && (L >= 0 && n >= 0 && C >= 0)) {

        // Given expanding formula
        double LL = (1 + n * C) * L;

        // Search all radians in circle (0 to 2*Pi)
        double res = binSearch(0, 2 * pi, LL, L);
        printf("%.9lf\n", res);
    }

    return 0;
}

