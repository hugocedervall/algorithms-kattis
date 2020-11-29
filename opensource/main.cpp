#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

int main() {


    string input;

    map<string, set<string>> persons;
    map<string, set<string>> signups;
    string latestOpenSource;

    while (getline(std::cin, input)) {
        if (input.compare("0") == 0) break;

        if (input.compare("1") == 0) {
            vector<pair<string, int>> results;
            for (auto & signup : signups) {
                results.push_back(make_pair(signup.first, signup.second.size()));
            }

            sort(results.begin(), results.end(),
                 [](pair<string, int> a, pair<string, int> b) {
                     return a.second != b.second ? a.second > b.second : a.first < b.first;
                 });

            for (auto & signup : results) {
                printf("%s %d\n", signup.first.c_str(), signup.second);
            }

            // print results
            persons.clear();
            signups.clear();

        } else {
            // If open source
            if (isupper(input[0])) {
                signups[input];
                latestOpenSource = input;
            }
                // Person signing up
            else {
                if (persons.find(input) != persons.end()) {
                    // If person only signed up for current project, its ok
                    if (persons[input].size() == 1 &&
                        persons[input].find(latestOpenSource) != persons[input].end())
                        continue;

                    // Erase all persons signups
                    for (auto signup : persons[input]) {
                        signups[signup].erase(input);
                    }
                    persons[input].clear();
                } else {
                    signups[latestOpenSource].insert(input);
                    persons[input].insert(latestOpenSource);
                }
            }
        }
    }

    return 0;
}

