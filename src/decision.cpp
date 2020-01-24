#include "decision.hpp"

bool hamming_dist_threshold(int l, int k, int s1, int s2, vector<int> const& S1, vector<int> const& S2){
    int i = s1;
    int j = s2;
    int res = 0;
    int mis = 0;
    int n = S1.size();
    while (res < l && i < n && j < n && mis <= k){
        if ( S1[i] != S2[j] ){
            mis++;
        }
        i++; j++;
        res++;
    }

    return (mis <= k && res >= l);
}

bool test_colisions(CollisionSet C, int l, int k, double eps, vector<int> const& S1, vector<int> const& S2) {
    int n = S1.size();
    if (C.random_collision.size() > 0){
        Collision c = C.random_collision[0];
        if (hamming_dist_threshold(l, (1 + eps) * k, c.first_string, c.second_string - n, S1, S2)) {
	    return true;	
        }
    }
    for (Collision& c : C.collisions) {
        if (hamming_dist_threshold(l, k, c.first_string, c.second_string - n, S1, S2)) {
	     return true;	    
        }
    }
    return false;
}

bool LCSk_LSH_decision(int l, int k, double eps, vector<int> const& S1, vector<int> const& S2){
    int n = S1.size();
    if (l > S1.size()) return false;
    if (l == 0) return true;
    if ((1 + eps) * k >= l) return true;
    int L = ceil(pow((double) n, (double) 1 / (1+eps)) / 16);
    double p2 = 1 - (1 + eps) * k / n;
    int m = ceil(log((double) 1 / n) / log(p2));
    ProjectionSet H(L, m, n, l);
    CollisionSet C = generate_collisions(H, S1, S2);
    return test_colisions(C, l, k, eps, S1, S2);
}

