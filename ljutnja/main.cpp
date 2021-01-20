/**
 * @PROBLEM: ljutnja
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-20
 *
 * Comments:
 *  Binary search and greedy approach
 *
 * Complexity:
 *  O(n*log(M)) where: M = max amount of candies (2e9)
 *                     n = amount of wishess from children
 *
 * Learned:
 *  Pow() from <cmath> is not great with big numbers
 */

#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Performs binary search to find the minimum max amount of candies that
 * a child will have left after all candies have been distributed.
 *
 * @return maximum candies that at least one child will have
 */
uint64_t binarySearch(uint64_t candies, const uint64_t wishes[], uint64_t len, uint64_t minVal, uint64_t maxVal){
    uint64_t left = minVal, right=maxVal;

    while (left < right) {
        uint64_t maxCandies = (right + left) / 2;

        uint64_t given = 0;
        for (int i = 0; i < len; ++i) {
            // Give candy to those with demand over maxCandies
            if (wishes[i] > maxCandies) {
                given += wishes[i] - maxCandies;
            }
        }
        if (given <= candies) {
            right = maxCandies;
        } else {
            left = maxCandies + 1;
        }
    }
    return left;
}

/**
 * Performs binary search in order to find the max demand that at
 * least one child will have. With the given max demand, a greedy
 * approach is used to find a solution.
 *
 * @return powered amount of candies still demanded by each child
 */
uint64_t solution(uint64_t candy, uint64_t wishes[], uint64_t len) {
    // Binary search if kids can have max x amount of candies each
    uint64_t maxCandy = binarySearch(candy, wishes, len, 0, 2e9);

    // Now that maxCandy has been found, give candy to kids that want more than maxCandy
    // so they only have maxCandy in demand.
    int candiesLeft = candy;
    for (int i = 0; i < len; ++i) {
        if (wishes[i] > maxCandy) {
            uint64_t givCandies = wishes[i] - maxCandy;
            wishes[i] -= givCandies;
            candiesLeft -= givCandies;
        }
    }

    // There can still be more candies to give, just not 1 for every kid.
    // So distribute candy to those kids with maxCandy demand in order
    // to minimise the squared remaining demand.
    for (int i = 0; i < len; ++i) {
        if (candiesLeft > 0) {
            if (wishes[i] >= maxCandy && wishes[i] > 0) {
                wishes[i]--;
                candiesLeft--;
            }
        } else break;
    }

    // Count the squared demands
    uint64_t total = 0;
    for (int i = 0; i < len; ++i) {
        total += wishes[i] * wishes[i];
    }
    return total;
}


int main() {
    uint64_t N, M, tmp;
    scanf("%llu", &M);
    scanf("%llu", &N);

    uint64_t wishes[N];
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        wishes[i] = tmp;
    }

    sort(wishes, wishes + N);

    uint64_t missing = solution(M, wishes, N);
    cout << missing << endl;

    return 0;
}