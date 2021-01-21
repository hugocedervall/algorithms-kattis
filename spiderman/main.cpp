/**
 * @PROBLEM: spiderman
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-21
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
    string actions;
    int height;
    int maxHeight;
};

string UP = "U";
string DOWN = "D";

string solution(vector<int> distances) {
    node *top = new node();
    top->actions = UP;
    top->height = distances[0];
    top->maxHeight = distances[0];

    map<int, node *> leafs;
    leafs[top->height] = top;

    for (int i = 1; i < distances.size(); ++i) {
        map<int, node *> newLeafs;
        for (auto &it : leafs) {
            node *curr = it.second;

            node *upChild = new node();
            node *downChild = new node();

            upChild->actions = curr->actions + UP;
            downChild->actions = curr->actions + DOWN;

            upChild->height = curr->height + distances[i];
            upChild->maxHeight = max(upChild->height, curr->maxHeight);

            downChild->maxHeight = curr->maxHeight;
            downChild->height = curr->height - distances[i];

            // If height already exists, keep the one with lowest max height
            if (newLeafs.find(upChild->height) != newLeafs.end()) {
                if (newLeafs[upChild->height]->maxHeight > upChild->maxHeight) {
                    newLeafs[upChild->height] = upChild;
                } else { delete upChild; }
            } else {
                newLeafs[upChild->height] = upChild;
            }

            // Only add children with accepted height
            if (downChild->height >= 0) {
                // If height already exists, keep the one with lowest max height
                if (newLeafs.find(downChild->height) != newLeafs.end()) {
                    if (newLeafs[downChild->height]->maxHeight > downChild->maxHeight)
                        newLeafs[downChild->height] = downChild;
                } else {
                    newLeafs[downChild->height] = downChild;
                }
            } else { delete downChild; }
            delete curr;
        }
        leafs = newLeafs;
    }

    if (leafs.empty()) return "IMPOSSIBLE";
    node *bestNode = nullptr;
    for (auto &it : leafs) {
        node *n = it.second;
        if (n->height == 0) {
            if (bestNode == nullptr) { bestNode = n; }
            else if (n->maxHeight < bestNode->maxHeight) {
                bestNode = n;
            }
        }
    }
    if (bestNode == nullptr) return "IMPOSSIBLE";
    return bestNode->actions;
}


int main() {
    int N, M, d;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        vector<int> distances;
        scanf("%d", &M);

        string in;
        while (cin >> in) {
            if (cin.peek() == '\n') break;
            distances.push_back(stoi(in));
        }
        distances.push_back(stoi(in));

        string result = solution(distances);
        cout << result << endl;
    }
    return 0;
}