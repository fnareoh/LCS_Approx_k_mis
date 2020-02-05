#include "20q.hpp"
#include "ukkonen.hpp"

const int USE_LCS_HEURISTIC = true;
const int TWENTY_QUESTIONS_FACTOR = 2;

long long int LCSk_LSH_20q(int k, double eps,
    vector<int> const& S1, vector<int> const& S2) {
    assert(S1.size() == S2.size());
    int n = S1.size();

    SuffixTree ST;
    if (USE_SUFFIX_TREE) {
        vector<int> S;
        for (int i = 0; i < n; ++i) S.push_back(S1[i]);
        S.push_back(-2);
        for (int i = 0; i < n; ++i) S.push_back(S2[i]);
        S.push_back(-1);
        ST.Create_suffix_tree(&S, S.size());
        ST.Compute_suffix_arrays();
    }

    stack<pair<int, int>> trusted;
    int max_yes = 0, l, r;
    if (USE_SUFFIX_TREE && USE_LCS_HEURISTIC) {
        int lcs = ST.LCS(n, 2 * n + 1);
        l = lcs + k;
        r = min(n, (k + 1) * lcs + k);
    } else {
        l = 0; r = n;
    }
    trusted.push(make_pair(l, r));
    int nb_iter = 0;
    int steps = ceil(TWENTY_QUESTIONS_FACTOR * log2(r - l));

    while (r - l > 0 && nb_iter < steps) {
        int m = (l + r + 1) / 2;
        ++nb_iter;
        if (LCSk_LSH_decision(m, k, eps, S1, S2, ST)) {
            max_yes = max(max_yes, m);
            if (LCSk_LSH_decision(r, k, eps, S1, S2, ST)) {
                //incoherence: remove the last interval
                if (trusted.size() != 1) trusted.pop();
            }
            else {
                trusted.push(make_pair(m, r));
            }
        }
        else {
            if (LCSk_LSH_decision(l, k, eps, S1, S2, ST)) {
                trusted.push(make_pair(l, m - 1));
            }
            else {
                //incoherence: remove the last interval
                if (trusted.size() != 1) trusted.pop();
            }
        }
        l = trusted.top().first;
        r = trusted.top().second;
    }
    if (USE_SUFFIX_TREE) {
        ST.Delete_suffix_tree();
    }
    return max_yes;
}
