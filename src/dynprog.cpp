#include "dynprog.hpp"

int dynprog(std::vector<int> const& S1, std::vector<int> const& S2, int k) {
    int n = S1.size();
    int m = S2.size();
    int l = 0;
    int r1 = 0;
    int r2 = 0;
    for(int d = -m +1; d < n; d++){
        int i = std::max(-d, 0) + d;
        int j = std::max(-d, 0);
        std::queue<int> Q;
        int s = 0;
        int p = 0;
        while (p <= std::min(n-i, m-j) - 1) {
            if (S1[i + p] != S2[j + p]) {
                if (Q.size() == k) {
                    s = Q.front() + 1;
                    Q.pop();
                }
                Q.push(p);
            }
            p++;
            if (p - s > l) {
                l = p - s;
                r1 = i + s;
                r2 = j + s;
            }
        }
    }
    return l;
}

