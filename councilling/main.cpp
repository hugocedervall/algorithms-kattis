/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-22
 * @PROBLEM: councilling
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Represents capacity in a edge. Used to keep track of
// used capacity and remaining capacity.
struct cap {
    int remain = 0, used = 0;
};

struct NodeID {
    unordered_map<string, int> nameToId{};
    unordered_map<string, int> partyToID{};
    unordered_map<string, int> clubToID{};

    unordered_map<int, string> idToName{};
    int nameCounter = 0, partyCount = 0, residentCount = 0, clubCount = 0;

    int getId(const string &name, const string &type = "") {
        if (type == "party") {
            if (partyToID.find(name) != partyToID.end()) return partyToID[name];
            partyCount++;
            partyToID[name] = nameCounter;
        } else if (type == "resident") {
            if (nameToId.find(name) != nameToId.end()) return nameToId[name];
            nameToId[name] = nameCounter;
            residentCount++;
        } else if (type == "club") {
            if (clubToID.find(name) != clubToID.end()) return clubToID[name];
            clubToID[name] = nameCounter;
            clubCount++;
        }
        idToName[nameCounter] = name;
        return nameCounter++;
    }
};


int bfs(int s, int t, vector<int> &parent, vector<vector<int>> &adj,
        vector<vector<cap>> &caps) {
    // Reset parents
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        // If in end node, return remain found flow
        if (curr.first == t) return curr.second;

        // For each neighbour of curr
        for (const auto &n : adj[curr.first]) {
            // If not marked and still have capacity
            if (parent[n] == -1 && caps[curr.first][n].remain > 0) {
                parent[n] = curr.first;
                int new_flow = min(curr.second, caps[curr.first][n].remain);
                if (n == t) return new_flow;
                q.push({n, new_flow});
            }
        }
    }
    return 0;
}

int
maxflow(int s, int t, vector<vector<int>> &adj, vector<vector<cap>> &capacities,
        NodeID &nodeId) {
    // Keep track of parents to nodes in path
    vector<int> parents(capacities.size(), -1);

    int flow = 0, new_flow;
    // For as long as there is still room for flow between s and t
    while ((new_flow = bfs(s, t, parents, adj, capacities)) != 0) {
        // Maximum flow found from start to end
        flow += new_flow;
        int curr = t;
        // Update flow used for each node on path
        while (curr != s) {
            int prev = parents[curr];
            capacities[prev][curr].used += new_flow;
            capacities[prev][curr].remain -= new_flow;
            capacities[curr][prev].used -= new_flow;
            capacities[curr][prev].remain += new_flow;

            curr = prev;
        }
    }
    return flow;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T, n;
    cin >> T;

    for (int caseNr = 0; caseNr < T; ++caseNr) {
        cin >> n;

        NodeID nodeId = NodeID{};
        int startID = nodeId.getId("startID"), endID = nodeId.getId("endID");

        // Mapping to keep track of edges and used flow
        unordered_map<int, unordered_map<int, cap>> tmpCaps;

        // List all residents
        vector<int> residents;

        // Want to map startnode to each party. Each part will point to
        // the person in that party, which in their turn will point to
        // their clubs, which will point to the ending node.
        unordered_map<int, vector<int>> tmpAdj;
        string person, party, club;
        int nrClubs, personID, partyID, clubID;
        for (int i = 0; i < n; ++i) {
            cin >> person >> party >> nrClubs;
            personID = nodeId.getId(person, "resident"), partyID = nodeId.getId(party, "party");
            // Add person to party
            tmpAdj[partyID].push_back(personID);
            tmpAdj[personID].push_back(partyID);

            residents.push_back(personID);

            tmpCaps[partyID][personID].remain = 1;

            // Add party to start
            tmpAdj[startID].push_back(partyID);

            tmpCaps[startID][partyID].remain = 1;

            for (int j = 0; j < nrClubs; ++j) {
                cin >> club;
                clubID = nodeId.getId(club, "club");
                // Add club to person
                tmpAdj[personID].push_back(clubID);
                tmpAdj[clubID].push_back(personID);

                tmpCaps[personID][clubID].remain = 1;

                // Add end to person
                tmpAdj[clubID].push_back(endID);

                tmpCaps[clubID][endID].remain = 1;
            }
        }
        // Change flow from start to each party, since each party max can have
        // Amount of partys divided by 2
        int maxStartFlow = (nodeId.clubCount - 1) / 2;

        for (auto &a : tmpAdj[startID]) {
            tmpCaps[startID][a].remain = maxStartFlow;
        }

        // Vector will be much faster, transform all data from map to fixed sized vector
        vector<vector<cap>> caps(nodeId.nameCounter, vector<cap>(nodeId.nameCounter));
        for (int i = 0; i < nodeId.nameCounter; ++i)
            for (auto &j : tmpAdj[i])
                caps[i][j] = tmpCaps[i][j];

        // Transform map into vector, will be much faster
        vector<vector<int>> adj(nodeId.nameCounter, vector<int>());
        for (int i = 0; i < nodeId.nameCounter; ++i)
            adj[i] = tmpAdj[i];

        int res = maxflow(startID, endID, adj, caps, nodeId);

        if (res == nodeId.clubCount) {
            //cout << res << '\n';
            for (auto &r : residents) {
                for (auto &neigh : tmpAdj[r]) {
                    if (caps[r][neigh].used > 0) {
                        cout << nodeId.idToName[r] << " " << nodeId.idToName[neigh] << '\n';
                        break;
                    }
                }
            }
        } else {
            cout << "Impossible." << '\n';
        }
    }
    cout << flush;

    return 0;
}
