#include "20q.hpp"

long long int LCSk_LSH_20q(int k, double eps,
    std::vector<int> const& S1, std::vector<int> const& S2,
    std::function<bool(int,int,double,
    std::vector<int> const&, std::vector<int> const&)> f) {
    assert(S1.size() == S2.size());
    int n = S1.size();

    std::stack<std::pair<int,int>> trusted;
    int max_yes = 0;
    trusted.push(std::make_pair(0, n + 1));
    int l = 0;
    int r = n + 1;
    int nb_iter = 0;

    while(r - l > 1 && nb_iter < ceil(log2(n))) { //ceil(16 * log2(n))){
        int m = std::ceil((l + r) / 2);
        nb_iter++;
        if (f(m, k, eps, S1, S2)) {
            max_yes = std::max(max_yes, m);
            if ( f(r, k, eps, S1, S2)) {
                //incoherence: remove the last interval
                if (trusted.size() != 1) trusted.pop();
            }
            else {
                trusted.push(std::make_pair(m, r));
            }
        }
        else {
            if (f(l, k, eps, S1, S2)) {
                trusted.push(std::make_pair(l, m));
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
    std::vector<int> const& S1, std::vector<int> const& S2) {
    return LCSk_LSH_20q(k, eps, S1, S2, LCSk_LSH_decision);
}

