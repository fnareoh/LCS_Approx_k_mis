#include "NTT.hpp"

typedef unsigned long long ULL;

const unsigned P = 2013265921; //15*2^27+1
const unsigned ROOT = 440564289; //root
const int MN = 21; // must be < 27
unsigned omega[1 << MN];

unsigned pw(unsigned x, unsigned n) {
    //raise x to the power n
    unsigned res = 1;
    while (n) {
        if (n & 1) res = (ULL) res * x % P;
        x = (ULL) x * x % P;
        n >>= 1;
    }
    return res;
}

void fft(vector<unsigned> &a, int n, bool inverse = false) {
    //(direct/inverse) FFT transform of A
    int N = 1 << n;
    a.insert(a.end(), N - a.size(), 0); //vector of size 2^n
    unsigned root = pw(ROOT, (1 << 27) / N * (inverse?(N - 1):1));
    omega[0] = 1;
    for (int i = 1; i < N - 1; ++i)
        omega[i] = (ULL) omega[i - 1] * root % P;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << i); ++j) {
            for (int k = 0; k < (1 << (n - i - 1)); ++k) {
                int s = (j << (n - i)) + k;
                int t = s + (1 << (n - i - 1));
                unsigned w = omega[k << i];
                unsigned temp = a[s] + a[t];
                if (temp >= P) temp -= P;
                unsigned t2 = a[s] - a[t] + P;
                a[t] = (ULL) w * t2 % P;
                a[s] = temp;
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        int x = i, y = 0;
        for (int j = 0; j < n; ++j)
            y = (y << 1) + (x & 1), x >>= 1;
        if (i < y) swap(a[i], a[y]);
    }
    if (inverse) {
        unsigned inv = pw(N, P - 2);
        for (int i = 0; i < N; ++i)
            a[i] = (ULL) a[i] * inv % P;
    }
}

vector<unsigned> conv(vector<unsigned> A, vector<unsigned> B) {
    //compute the convolution of A and B
    int n = 31 - __builtin_clz(2 * (A.size() + B.size()) - 1);
    fft(A, n);
    fft(B, n);
    for (int i = 0; i < (1 << n); ++i)
        A[i] = (ULL) A[i] * B[i] % P;
    fft(A, n, true);
    return A;
}
