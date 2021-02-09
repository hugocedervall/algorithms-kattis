/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-08
 * @PROBLEM: polymul2
 *      Given two polynomials of given degrees, the task is
 *      to multiply these polynomials and output the product
 *      in an efficient method. This is solved by transforming
 *      the polynomials into the frequency domain, multiplying
 *      them, and then transforming them back into time domain.
 *      This is possible since convolution in time domain is
 *      the same as multiplication in frequency domain.
 *
 * @COMPLEXITIES:
 *      TIME: O(n*log(n))
 *          Both fast fourier transform and inverse fast fourier
 *          transform have time complexities O(n*log(n)), the total
 *          complexity will be the same.
 *
*/

#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <complex>


using namespace std;

typedef complex<double> compd;

/**
 * Cooley–Tukey FFT algorithm (fast fourier transform). Computes the fourier transform
 * of input in O(n*log(n)) where n is amount of elements in input. Implemented from
 * pseudo code from: https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
 *
 * @param poly complex polynomial coefficients in time domain. This polynomial values
 * will be replaced with the values in the frequency domain.
 */
void fft(vector<compd> &poly) {
    int n = poly.size();
    if (poly.size() == 1) return;

    // Divide into odd/even polys, this is the "magic" which
    // makes the algorithm O(n*log(n)) instead of O(n^2)
    vector<compd> polyEven(n / 2), polyOdd(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        polyEven[i] = poly[2 * i];
        polyOdd[i] = poly[2 * i + 1];
    }

    vector<compd> unityRoots(n);
    for (int i = 0; i < n; ++i) {
        // Complex representation, same as (cos, sin) of theta
        // with magnitude 1
        unityRoots[i] = polar(1.0, -2 * M_PI * i / n);
    }

    // Resursively calculate the fft of even/odd polys independently
    fft(polyEven);
    fft(polyOdd);

    for (int k = 0; k < n / 2; ++k) {
        poly[k] = polyEven[k] + unityRoots[k] * polyOdd[k];
        poly[k + n / 2] = polyEven[k] - unityRoots[k] * polyOdd[k];
    }
}

/**
 * Inverse of Fast Fourier Transform (ifft), transforms
 * the given complex numbers from frequency domain to
 * time domain. Formula found here:
 *  https://rosettacode.org/wiki/Fast_Fourier_transform
 *
 * @param fPoly complex polynomial coefficients in frequency
 * domain, this object will be changed into the inverse
 * fourier transform of its initial state
 */
void ifft(vector<compd> &fPoly) {
    vector<compd> res(fPoly.size());
    for (auto &i : fPoly)
        i = conj(i);

    fft(fPoly);

    for (auto &i : fPoly)
        i = conj(i);
    for (int i = 0; i < fPoly.size(); ++i)
        fPoly[i] /= fPoly.size();
}

/**
 * Multiplies @param poly1 and @param poly2. This is done in the
 * frequency domain, since is can be done in O(n*log(n)).
 * This is the same as the convolution in the time domain.
 *
 * @param poly1 polynomial coefficients that shall be convoluted
 * @param poly2 polynomial coefficients that shall be convoluted
 * @return The product of @param poly1 and @param poly2
 */
vector<int> polyMult(vector<compd> &poly1, vector<compd> &poly2) {
    // Fourier Transform
    fft(poly1);
    fft(poly2);

    // Product in frequence domain
    vector<compd> product(poly1.size());
    for (int i = 0; i < poly1.size(); ++i) {
        product[i] = poly1[i] * poly2[i];
    }
    // Inverse Fourier Transform
    ifft(product);
    vector<int> res(product.size());
    for (int i = 0; i < product.size(); ++i) {
        res[i] = round(real(product[i]));
    }
    // Product polynomial
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T, n1, n2;
    double tmp;
    cin >> T;

    while (T--) {
        cin >> n1;
        vector<compd> poly1(n1 + 1, 0);
        for (int i = 0; i <= n1; ++i) {
            cin >> tmp;
            poly1[i] = {tmp, 0};
        }
        cin >> n2;
        vector<compd> poly2(n2 + 1, 0);
        for (int i = 0; i <= n2; ++i) {
            cin >> tmp;
            poly2[i] = {tmp, 0};
        }

        // Since resulting polynomial can be much larger than
        // poly1 and poly2, create bigger vectors on the total size
        int maxSize = n1 + n2 + 2;
        // Find next power of 2 which is bigger than maxSize, since the fft
        // requires log2(n) to be even.
        maxSize = pow(2, ceil(log(maxSize) / log(2)));
        vector<compd> poly1R(maxSize, 0);
        vector<compd> poly2R(maxSize, 0);
        for (int i = 0; i < poly1.size(); ++i)
            poly1R[i] = poly1[i];
        for (int i = 0; i < poly2.size(); ++i)
            poly2R[i] = poly2[i];

        vector<int> res = polyMult(poly1R, poly2R);
        // Remove trailing zeros
        int i;
        for (i = res.size() - 1; i > 0; --i)
            if (res[i] != 0) break;

        cout << i << '\n';
        if (i > 0) {
            for (int j = 0; j <= i; ++j)
                cout << res[j] << " ";
            cout << '\n';
        }
    }
    cout << flush;
    return 0;
}
