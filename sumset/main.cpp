#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include<tuple>

using namespace std;


tuple<int, bool> algo(const set<int> &numbers) {
    // number -> pairs used to construct number
    map<int, vector<tuple<int, int>>> doubleNumbers;


    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        for (auto it2 = next(it); it2 != numbers.end(); it2++) {
            doubleNumbers[*it2 + *it].push_back(make_tuple(*it, *it2));
        }
    }


    int biggest = *min_element(numbers.begin(), numbers.end());
    bool valid = false;

    for (auto d : numbers) {
        for (auto c: numbers) {
            if (d == c) continue;

            if (doubleNumbers.find(d - c) != doubleNumbers.end()) {
                bool found = false;
                // Check that c or d has not been used in composition of a+b+c=d before.
                for (tuple<int, int> nums : doubleNumbers[d - c]) {
                    if (get<0>(nums) == c || get<1>(nums) == c || get<0>(nums) == d || get<1>(nums) == d) {
                        found = true;
                        break;
                    }
                }
                if (!found && d >= biggest) {
                    biggest = d;
                    valid = true;
                    //break;
                }
            }

        }

    }

    return make_tuple(biggest, valid);
}


int main() {


    int N;
    while(cin >> N && N != 0) {

        set<int> numbers;
        for (int i = 0; i < N; i++) {
            int temp;
            cin >> temp;
            numbers.insert(temp);
        }

        tuple<int, bool> results = algo(numbers);

        if (!get<1>(results)) cout << "no solution" << endl;
        else cout << get<0>(results) << endl;
    }
    return 0;
}
