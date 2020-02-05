#include "decision.hpp"

const double L_FACTOR = 1./16.;

inline bool hamming_dist_threshold(int l, int k, int s1, int s2,
    vector<int> const& S1, vector<int> const& S2,
    SuffixTree &ST) {
    int n = S1.size();
    int res = 0;
    int mis = 0;
    if (USE_SUFFIX_TREE) {
        while (res < l && mis < k) {
            res += ST.LCE(s1 + res, n + 1 + s2 + res) + 1;
            ++mis;
        }
        if (res < l && mis == k)
            res += ST.LCE(s1 + res, n + 1 + s2 + res);
    } else {
        int i = s1, j = s2;
        while (res < l && i < n && j < n && mis <= k) {
            if (S1[i] != S2[j])
                ++mis;
            ++i; ++j;
            ++res;
        }
    }
    return mis <= k && res >= l;
}

bool test_colisions(CollisionSet C, int l, int k, double eps,
    vector<int> const& S1, vector<int> const& S2,
    SuffixTree &ST) {
    int n = S1.size();
    if (!C.random_collision.empty()) {
        Collision c = C.random_collision[0];
        if (hamming_dist_threshold(l, (1 + eps) * k, c.first_string, c.second_string - n, S1, S2, ST))
            return true;
    }
    for (Collision& c : C.collisions)
        if (hamming_dist_threshold(l, k, c.first_string, c.second_string - n, S1, S2, ST))
            return true;
    return false;
}

bool LCSk_LSH_decision(int l, int k, double eps,
    vector<int> const& S1, vector<int> const& S2,
    SuffixTree &ST) {
    int n = S1.size();
    if (l > S1.size()) return false;
    if (l == 0) return true;
    if ((1 + eps) * k >= l) return true;
    int L = ceil(pow((double)n, 1. / (1 + eps)) * L_FACTOR);
    double p2 = 1 - (1 + eps) * k / n;
    int m = ceil(log(1. / n) / log(p2));
    ProjectionSet H(L, m, n, l);
    CollisionSet C = generate_collisions(H, S1, S2);
    return test_colisions(C, l, k, eps, S1, S2, ST);
}
