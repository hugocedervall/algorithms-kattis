#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct node {
    bool marked = false;
    vector<int> children;
    vector<int> parents;
};

// If nodes all parents are marked
bool visitedParents(int n, map<int, node> &nodes) {
    for (int p : nodes[n].parents) {
        if (!nodes[p].marked) return false;
    }
    return true;
}

// Nodes that do not have any parent that is not visited
vector<int> getFreeNodes(map<int, node> &nodes) {
    vector<int> freeNodes;
    for (auto n : nodes) {
        if (!n.second.marked && visitedParents(n.first, nodes)) freeNodes.push_back(n.first);
    }
    return freeNodes;
}

vector<set<int>> algorithm(int num, map<int, node> nodes) {
    auto freeNodes = getFreeNodes(nodes);
    vector<set<int>> combinations;
    for (auto n : freeNodes) {
        int temp = num - 1;
        if (temp == 0) {
            combinations.push_back(set<int>{n});
            continue;
        }
        auto nodesCopy = nodes;
        nodesCopy[n].marked = true;
        auto newCombos = algorithm(temp, nodesCopy);
        for (auto s : newCombos) {
            s.insert(n);
            combinations.push_back(s);
        }
    }
    return combinations;

}

// Returns intersection between given sets
set<int> setIntersection(vector<set<int>> sets) {
    set<int> intersection;
    if (sets.size()) intersection = sets.at(0);
    for (auto s : sets) {
        set<int> tempIntersection;
        set_intersection(intersection.begin(), intersection.end(), s.begin(), s.end(),
                         inserter(tempIntersection, tempIntersection.begin()));
        intersection = tempIntersection;
    }
    return intersection;
}

int main() {

    int A, B, E, P;

    while (cin >> A >> B >> E >> P) {

        map<int, node> nodes;

        // Create nodes for all
        for (int i = 0; i < E; ++i) {
            node temp;
            nodes[i] = temp;
        }

        for (int i = 0; i < P; ++i) {
            int a, b;
            cin >> a >> b;
            nodes[a].children.push_back(b);
            nodes[b].parents.push_back(a);
        }

        auto solutionA = algorithm(A, nodes);
        auto solutionB = algorithm(B, nodes);

        // Which nodes that appear in every solution
        auto s1 = setIntersection(solutionA);
        auto s2 = setIntersection(solutionB);

        // See which nodes that can be chosen
        set<int> s3;
        for (auto s : solutionB) {
            s3.insert(s.begin(), s.end());
        }

        cout << s1.size() << endl;
        cout << s2.size() << endl;
        cout << E - s3.size() << endl;
    }

    return 0;
}
