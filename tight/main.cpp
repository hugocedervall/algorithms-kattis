#include <iostream>
#include <vector>
#include <cmath>
#include <limits> // To get full output
#include <map>
#include<stdio.h> // If submitting to UVA

using namespace std;

// Used to dynamically save previous computations
// K -> start number -> remaining length -> results
map<int, map<int, map<int, double>>> memory;

void fillMemoryMatrix() {
    int maxNumber = 9;
    int maxLength = 100;
    for (int i = 0; i <= maxNumber; i++) {
        for (int j = 0; j <= maxNumber; j++) {
            for (int k = 0; k <= maxLength; k++) {
                memory[i][j][k] = -1;
            }
        }
    }
}

double tightWords(map<int, vector<int>> &neighbourLookup, int maxNumber, int remainingLength,
                  vector<int> const &neighbours) {
    if (remainingLength <= 1) return neighbours.size();

    double total = 0;
    for (int neigh: neighbours) {

        double dynamicRes = memory[maxNumber][neigh][remainingLength];

        // If not already computed
        if (dynamicRes == -1) {
            double res = tightWords(neighbourLookup, maxNumber, remainingLength - 1, neighbourLookup[neigh]);

            // Save computations
            memory[maxNumber][neigh][remainingLength] = res;
            total += res;
        } else {
            total += dynamicRes;
        }
    }

    return total;
}


double tight(int k, int n) {
    double tightAmount = 0;

    // Amount of words of length n
    double totalAmount = pow(k + 1, n);

    // Build alphabet
    vector<int> alphabet;
    for (int i = 0; i <= k; i++) {
        alphabet.push_back(i);
    }

    // Lookup to check which neighbours a number has
    map<int, vector<int>> neighbourLookup;
    for (int character : alphabet) {
        vector<int> currNeigh;
        currNeigh.push_back(character);
        if (character != 0)
            currNeigh.push_back(character - 1);
        if (character != k)
            currNeigh.push_back(character + 1);
        neighbourLookup[character] = currNeigh;
    }

    tightAmount = tightWords(neighbourLookup, k, n, alphabet);

    return tightAmount / totalAmount * 100.0;
}


int main() {
    fillMemoryMatrix();

    int k, n;
    while (cin >> k >> n) {
        double res = tight(k, n);
        cout.precision(numeric_limits<double>::max_digits10);
        cout << res << endl;

        /*
         UVA requires exacly 5 decimals to accept solution:
         printf("%0.5f\n", res);
        */
    }
    return 0;
}
