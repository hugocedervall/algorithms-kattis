#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include<tuple>

using namespace std;


int algo(const set<int> & numbers) {
    // number -> pairs used to construct number
    map<int, vector<tuple<int, int>>> doubleNumbers;


    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        for (auto it2 = next(it); it2 != numbers.end(); it2++){
            doubleNumbers[*it2 + *it].push_back(make_tuple(*it, *it2));
        }
    }


    map<int, vector<tuple<int,int,int>>> trippleNumbers;
    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        for (auto it2 = doubleNumbers.begin(); it2 != doubleNumbers.end(); it2++){
            tuple<int,int,int> a = make_tuple(*it, get<0>(it2->second), get<1>(it2->second)[1]);
            //trippleNumbers[*it + it2->first].push_back();
        }
    }


    int biggest = 0;
    for (auto num : numbers) {
        if (find(trippleNumbers.begin(), trippleNumbers.end(), num) != trippleNumbers.end()) {
            biggest = num;
        }
    }

    return biggest;
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

    int results = algo(numbers);

    if (results == 0) cout << "no solution" << endl;
    else cout << results << endl;

    return 0;
}
