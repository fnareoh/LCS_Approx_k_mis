#include "dynprog.hpp"

int dynprog(vector<int> const& S1, vector<int> const& S2, int k) {
    int n1 = S1.size();
    int n2 = S2.size();
    int l = 0;
    for (int d = -n2 + 1; d < n1; d++) {
        int i = max(-d, 0) + d;
        int j = max(-d, 0);
        queue<int> Q;
        int s = 0;
        int p = 0;
        while (p <= min(n1 - i, n2 - j) - 1) {
            if (S1[i + p] != S2[j + p]) {
                if (Q.size() == k) {
                    s = Q.front() + 1;
                    Q.pop();
                }
                Q.push(p);
            }
            ++p;
            if (p - s > l)
                l = p - s;
        }
    }
    return l;
}
