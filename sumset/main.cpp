#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include<tuple>

using namespace std;

tuple<int, bool> algo(const set<int> &numbers) {
    // number -> tuple used to construct number
    unordered_map<int, vector<tuple<int, int>>> doubleNumbers;

    // All possible permutations for 2 numbers of set
    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        for (auto it2 = next(it); it2 != numbers.end(); it2++) {
            doubleNumbers[*it2 + *it].push_back(make_tuple(*it, *it2));
        }
    }

    int min = *min_element(numbers.begin(), numbers.end());

    // Biggest found d
    int biggest = min - 1;

    for (auto d : numbers) {
        for (auto c: numbers) {
            if (d == c) continue;

            if (doubleNumbers.find(d - c) != doubleNumbers.end()) {

                // See if there is a tuple not containing a or b that constructs d - c
                bool found = false;
                for (tuple<int, int> nums : doubleNumbers[d - c]) {
                    int a = get<0>(nums);
                    int b = get<1>(nums);
                    if (a != c && b != c && a != d && b != d) {
                        found = true;
                        break;
                    }
                }

                if (found && d > biggest) {
                    biggest = d;
                    break;
                }
            }
        }
    }

    return make_tuple(biggest, (biggest > min - 1));
}


int main() {
    int N;
    cin >> N;

    set<int> numbers;
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        numbers.insert(temp);
    }

    tuple<int, bool> results = algo(numbers);

    if (!get<1>(results)) cout << "no solution" << endl;
    else cout << get<0>(results) << endl;

    return 0;
}
