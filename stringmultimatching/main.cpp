
/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-09
 * @PROBLEM: stringmultimatching
 *      The problem is to find all positions where given patterns occures
 *      in a given text. This is solved with Aho-Corasick algorithm.
 * @COMPLEXITIES:
 *      TIME: O(N + M + Z), N = length of text, M = amount of patterns, Z = count of matches
 *
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int FIRST_CHAR = '\032';
const int ROOT_NODE = 0;

int charToInt(const char &c) {
    return c - FIRST_CHAR;
}

/**
 * Represents a Node which is used to build Trie.
 */
struct Node {
    int patternInd = -1, outputLink = -1, suffixLink = 0;
    int charNr, nodeNr;
    // Adj nodes from current
    map<int, int> children;

    Node(int c = 0, int i = -1, int nodeNr = 0) {
        this->charNr = c;
        this->nodeNr = nodeNr;
        this->patternInd = i;

    }
};

/**
 * Trie is a type of search tree where each node represents
 * a character. This can be used to search for strings.
 */
struct Trie {
    vector<Node> nodes;

    Trie() {
        // Initially only add root node
        nodes = vector<Node>(1);
    }

    /**
     * Adds given @param s  to trie. This is done by traversing
     * the trie and adding nodes for characters where there are
     * none.
     *
     * @param s a pattern
     * @param i pattern index of given @param s
     */
    void addString(const string &s, int i) {
        int node = ROOT_NODE;
        for (auto &c : s) {
            int nr = charToInt(c);
            // If current node doesn't point to node with next character
            if (nodes[node].children.find(nr) == nodes[node].children.end()) {
                int newNodeNr = nodes.size();
                nodes[node].children[nr] = newNodeNr;
                // add new node since not already present
                nodes.emplace_back(nr, -1, newNodeNr);
            }
            node = nodes[nodes[node].children[nr]].nodeNr;
        }
        // Last char will be leaf, whole seq then represents pattern
        nodes[node].patternInd = i;
    }
};

/**
 * Implementation of the Aho-Corasick Algorithm.
 * From a given set of patterns it constructs a finite state
 * machine with a trie that contains additional links between
 * nodes.
 * This trie can then be used with a text to find the
 * occurances of the patterns in the text.
 */
class Aho {
private:
    Trie trie;
    /* Mapping from pattern to first occurance of pattern
     used to not recompute same patters */
    unordered_map<string, int> patternToIndx;

    /* Only compute results for unique patterns, but give
     results for all patterns */
    vector<string> allPatterns;
    vector<string> uniquePatterns;

    /**
     * Add all unique patterns to the trie
     */
    void addPatterns() {
        int i = 0;
        for (const auto &p : this->uniquePatterns)
            trie.addString(p, i++);
    }

    /**
     * Creates suffix and output links between nodes.
     * A suffix link for a node is a edge that points to the longest
     * proper suffix of the string corresponding to the node.
     * A output link is the same as a suffix link but it only exists
     * when the edge points to a node which is a complete pattern (the
     * end character of a pattern).
     */
    void buildSuffixAndOutputLinks() {
        // Point root suffix link to itself
        trie.nodes[ROOT_NODE].suffixLink = ROOT_NODE;

        queue<int> q;

        // Add all childs of root to queue
        for (auto &child : trie.nodes[ROOT_NODE].children)
            q.push(child.second);

        // Breadth-first search to compute suffix links
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            // All childs of curr
            for (auto &child : trie.nodes[cur].children) {
                int charNr = trie.nodes[child.second].charNr;
                int suffixLink = trie.nodes[cur].suffixLink;

                // Find longest proper suffix
                while (trie.nodes[suffixLink].children.find(charNr) == trie.nodes[suffixLink].children.end() &&
                       suffixLink != ROOT_NODE)
                    suffixLink = trie.nodes[suffixLink].suffixLink;

                // If proper suffix was found
                if (trie.nodes[suffixLink].children.find(charNr) != trie.nodes[suffixLink].children.end()) {
                    trie.nodes[child.second].suffixLink = trie.nodes[trie.nodes[suffixLink].children[charNr]].nodeNr;
                } else {
                    trie.nodes[child.second].suffixLink = ROOT_NODE;
                }
                q.push(child.second);
            }

            // Setup output links if node pointed to is a complete pattern
            if (trie.nodes[trie.nodes[cur].suffixLink].patternInd != -1) {
                trie.nodes[cur].outputLink = trie.nodes[cur].suffixLink;
            } else {
                trie.nodes[cur].outputLink = trie.nodes[trie.nodes[cur].suffixLink].outputLink;
            }
        }
    }

public:

    explicit Aho(const vector<string> &patterns) {
        this->allPatterns = patterns;

        // Handle  only unique patterns
        for (const auto &pattern : patterns)
            // If not seen before
            if (this->patternToIndx.find(pattern) == this->patternToIndx.end()) {
                this->patternToIndx.insert({pattern, this->uniquePatterns.size()});
                this->uniquePatterns.push_back(pattern);
            }

        trie = Trie{};
        this->addPatterns();
        this->buildSuffixAndOutputLinks();
    }

    /**
     * Searches through @param text for all occurances of all patterns
     * that the object contains.
     *
     * @param text The text to search for occurances of patterns in
     * @param res For each pattern, all the positions of occurances for
     * the pattern in the text. The positions are specified by the last
     * index in the pattern. Example: text = "hej", pattern="ej" -> 2
     */
    void searchWords(const string &text, vector<vector<int>> &res) {
        vector<vector<int>> uniqueRes = vector<vector<int>>(this->uniquePatterns.size());

        int parent = ROOT_NODE;
        for (int i = 0; i < text.length(); ++i) {
            int charNr = charToInt(text[i]);
            // If link to character exists, follow it
            if (trie.nodes[parent].children.find(charNr) != trie.nodes[parent].children.end()) {
                parent = trie.nodes[trie.nodes[parent].children[charNr]].nodeNr;

                if (trie.nodes[parent].patternInd != -1)
                    uniqueRes[trie.nodes[parent].patternInd].push_back(i);

                int temp = trie.nodes[parent].outputLink;
                while (temp != -1) {
                    uniqueRes[trie.nodes[temp].patternInd].push_back(i);
                    temp = trie.nodes[temp].outputLink;
                }
            } else {
                // Follow suffix links until matching suffix or root node found
                while (parent != ROOT_NODE &&
                       trie.nodes[parent].children.find(charNr) == trie.nodes[parent].children.end())
                    parent = trie.nodes[parent].suffixLink;
                // Has charNr as child
                if (trie.nodes[parent].children.find(charNr) != trie.nodes[parent].children.end())
                    i--;
            }
        }

        // Insert unique solutions
        for (int i = 0; i < res.size(); ++i) {
            int index = this->patternToIndx[this->allPatterns[i]];
            res[i] = uniqueRes[index];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string text, line;
    while (cin >> n) {
        getline(cin, line);
        vector<string> patterns(n);
        for (int i = 0; i < n; ++i)
            getline(cin, patterns[i]);

        getline(cin, text);
        Aho aho = Aho(patterns);
        vector<vector<int>> res = vector<vector<int>>(patterns.size());
        aho.searchWords(text, res);

        for (int i = 0; i < patterns.size(); ++i) {
            for (auto &j : res[i])
                // contains info when pattern end, so subtract len
                cout << j - patterns[i].length() + 1 << " ";
            cout << '\n';
        }
    }
    cout << flush;

    return 0;
}