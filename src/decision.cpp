#include "decision.hpp"

bool hamming_distance_threshold(vector<int> const& S1, vector<int> const& S2, int l,
    double mismatches, int s1, int s2){

    int i = s1;
    int j = s2;
    int res = 0;
    int mis = 0;
    while ( res < l && i < S1.size() && j < S2.size() && mis <= mismatches){
        if ( S1[i] != S2[j] ){
            mis++;
        }
        i++; j++;
        res++;
    }

    return (mis <= mismatches && res >= l);
}

bool test_colisions(CollisionSet C, int n, int l, int k, double eps,
    function<bool(int,double,
    int, int)> test_function) {
    if (C.random_collision.size() > 0){
        Collision c = C.random_collision[0];
        if (test_function(l, (1 + eps) * k, 
        c.first_string, 
        c.second_string - n))
        {
            return true;
        }
    }
    for (Collision& c : C.collisions) {
        if (test_function(l, k, 
                        c.first_string,
                        c.second_string - n))
            {
                return true;
            }
    }
    return false;
}

bool LCSk_LSH_decision(int l, int k, double eps,
    vector<int> const& S1, vector<int> const& S2){
    assert(S1.size() ==  S2.size());
    if (l > S1.size()) return false;
    if (l == 0) return true;
    if ((1+eps) * k >= l) return true;

    int n = S1.size();
    
    int L = ceil(pow((double) n, (double) 1 / (1+eps)) / 16);

    double p2 = 1 - (1 + eps) * k / n;
    int m = ceil(log((double) 1 / n) / log(p2));
    ProjectionSet H(L, m, n, l);
    CollisionSet C = generate_collisions(H, S1, S2);

    auto test = [S1, S2](int l, double k, int n1, int n2) ->
    bool { return hamming_distance_threshold(S1, S2, l, k, n1, n2); };

    return test_colisions(C, n, l, k, eps, test);
}

