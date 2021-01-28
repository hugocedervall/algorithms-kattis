/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-01-28
 * @PROBLEM: setstack
*/

#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include <stack>


using namespace std;

// unique set to id
map<set<int>, int> setId;
// int to set
map<int, set<int>> idSet;

int push(stack<int> &s, map<set<int>, int> &stackSizes) {
    set<int> tmpSet = {};
    if (setId.find(tmpSet) == setId.end()) {
        int id = setId.size();
        setId[tmpSet] = id;
        idSet[id] = tmpSet;
    }
    // Push id
    s.push(setId[tmpSet]);
    return tmpSet.size();
}

int dup(stack<int> &s, map<set<int>, int> &stackSizes) {
    s.push(s.top());
    set<int> tmpSet = idSet[s.top()];
    return tmpSet.size();
}

int uni(stack<int> &s, map<set<int>, int> &stackSizes) {
    int A = s.top();
    set<int> a = idSet[A];
    s.pop();
    int B = s.top();
    set<int> b = idSet[B];
    s.pop();

    set<int> tmpSet;
    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(tmpSet, tmpSet.begin()));

    if (setId.find(tmpSet) == setId.end()) {
        int id = setId.size();
        setId[tmpSet] = id;
        idSet[id] = tmpSet;
    }
    s.push(setId[tmpSet]);

    return tmpSet.size();
}

int intersect(stack<int> &s, map<set<int>, int> &stackSizes) {
    int A = s.top();
    set<int> a = idSet[A];
    s.pop();
    int B = s.top();
    set<int> b = idSet[B];
    s.pop();

    set<int> tmpSet;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(tmpSet, tmpSet.begin()));

    if (setId.find(tmpSet) == setId.end()) {
        int id = setId.size();
        setId[tmpSet] = id;
        idSet[id] = tmpSet;
    }
    s.push(setId[tmpSet]);

    return tmpSet.size();
}

int add(stack<int> &s, map<set<int>, int> &stackSizes) {
    int A = s.top();
    s.pop();
    int B = s.top();
    s.pop();

    set<int> tmpSet = idSet[B];
    tmpSet.insert(A);

    if (setId.find(tmpSet) == setId.end()) {
        int id = setId.size();
        setId[tmpSet] = id;
        idSet[id] = tmpSet;
    }

    s.push(setId[tmpSet]);
    return tmpSet.size();
}

vector<int> solution(vector<string> &commands) {
    setId.empty();
    idSet.empty();

    vector<int> res(commands.size(), 0);
    // Cardinalities after each operation
    unordered_map<string, int> commandToInt;
    commandToInt["PUSH"] = 0;
    commandToInt["DUP"] = 1;
    commandToInt["UNION"] = 2;
    commandToInt["INTERSECT"] = 3;
    commandToInt["ADD"] = 4;

    vector<int> intCommands(commands.size());
    for (int i = 0; i < intCommands.size(); ++i)
        intCommands[i] = commandToInt[commands[i]];

    // Stack
    stack<int> s;
    // Map sizes of stacks (the recursive size)
    map<set<int>, int> stackSizes;

    for (int i = 0; i < intCommands.size(); ++i) {
        //if (i == 0) continue;
        switch (intCommands[i]) {
            case 0: //"PUSH"
                res[i] = push(s, stackSizes);
                break;
            case 1: //"DUP"
                res[i] = dup(s, stackSizes);
                break;
            case 2: //"UNION"
                res[i] = uni(s, stackSizes);
                break;
            case 3: //"INTERSECT"
                res[i] = intersect(s, stackSizes);
                break;
            case 4: //"ADD"
                res[i] = add(s, stackSizes);
                break;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int cardi, n;
    string line;
    getline(cin, line);
    cardi = stoi(line);


    for (int i = 0; i < cardi; ++i) {
        getline(cin, line);
        n = stoi(line);
        vector<string> commands(n);
        for (int j = 0; j < n; ++j) {
            getline(cin, line);
            commands[j] = line;
        }
        vector<int> res = solution(commands);
        for (int j = 0; j < res.size(); ++j)
            cout << res[j] << endl;

        cout << "***" << endl;
    }


    return 0;
}