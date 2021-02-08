/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-02-08
 * @PROBLEM: longincsubseq
 *      Given a sequence, the problem is to find the longest
 *      subsequence, such that the numbers are in strict increasing order.
 *
 * @COMPLEXITIES:
 *      TIME: O(n*log(n)), where n is length of sequence
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/**
 * Calculates the longest increasing subsequence from the
 * given sequence. The indexes of the longest subsequence
 * will be returned. In case of multiple solutions, only
 * one solution will only be returned.
 *
 * @param seq sequence of integers
 * @return indexes for one of the longest incresing
 * subsequences.
 */
vector<int> lis(vector<int> &seq) {
    // Indexes represent sequence lengths, and elements represent the index of
    // the smallest number that produced the sequence length
    vector<int> seqLens(seq.size() + 1, 1);
    // Stores previous index of subsequence ending in index
    vector<int> seqs(seq.size());
    // Longest subsequence found
    int L = 0;
    int mid;
    for (int i = 0; i < seq.size(); ++i) {
        int lo = 1;
        int hi = L;
        // Binary search through previous subsequence lengths
        // to find where curr element could be added
        while (lo <= hi) {
            mid = ceil((lo + hi) / 2);
            if (seq[seqLens[mid]] < seq[i]) {
                lo = mid + 1;
            } else hi = mid - 1;
        }
        // Store index before current index to reach sequence length lo
        seqs[i] = seqLens[lo - 1];
        // Curr index was last in lo sequence length
        seqLens[lo] = i;
        // If new longer solution found
        if (lo > L) L = lo;
    }

    // Since the last index is represented in seqs,
    // the solution that gives L length can be derived
    // backwards from seqs.
    vector<int> res(L);
    int k = seqLens[L];
    for (int i = L - 1; i >= 0; --i) {
        res[i] = k;
        k = seqs[k];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<int> seq(n);
        for (int i = 0; i < n; ++i)
            cin >> seq[i];
        vector<int> res = lis(seq);
        cout << res.size() << '\n';
        if (!res.empty()) {
            for (auto &r : res) cout << r << " ";
            cout << '\n';
        }
    }
    cout << flush;
    return 0;
}
