#include "20q.hpp"

long long int LCSk_LSH_20q(int k, double eps,
    vector<int> const& S1, vector<int> const& S2,
    function<bool(int,int,double,
    vector<int> const&, vector<int> const&)> f) {
    assert(S1.size() == S2.size());
    int n = S1.size();

    stack<pair<int,int>> trusted;
    int max_yes = 0;
    trusted.push(make_pair(0, n + 1));
    int l = 0;
    int r = n + 1;
    int nb_iter = 0;

    while(r - l > 1 && nb_iter < ceil(2 * log2(n))) {
        int m = ceil((l + r) / 2);
        nb_iter++;
        if (f(m, k, eps, S1, S2)) {
            max_yes = max(max_yes, m);
            if ( f(r, k, eps, S1, S2)) {
                //incoherence: remove the last interval
                if (trusted.size() != 1) trusted.pop();
            }
            else {
                trusted.push(make_pair(m, r));
            }
        }
        else {
            if (f(l, k, eps, S1, S2)) {
                trusted.push(make_pair(l, m));
            }
            else {
                //incoherence: remove the last interval
                if (trusted.size() != 1) trusted.pop();
            }
        }
        l = trusted.top().first;
        r = trusted.top().second;
    }
    return max_yes;
}

long long int LCSk_LSH(int k, double eps,
    vector<int> const& S1, vector<int> const& S2) {
    return LCSk_LSH_20q(k, eps, S1, S2, LCSk_LSH_decision);
}

