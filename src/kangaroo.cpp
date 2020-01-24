#include "kangaroo.hpp"

Kangaroo::Kangaroo () {}

void Kangaroo::construct(std::vector<int> const& S_1, std::vector<int> const& S_2) {
    std::copy(S_1.begin(), S_1.end(), std::back_inserter(T));
    std::copy(S_2.begin(), S_2.end(), std::back_inserter(T));
    std::stringstream T_stream;
    std::copy(T.begin(), T.end(), std::ostream_iterator<int>(T_stream, " "));
    
    n1 = S_1.size();
    n2 = S_2.size();

    sdsl::construct_im(csa, T_stream.str(), 'd');
    sdsl::construct_im(lcp, T_stream.str(), 'd');
    sdsl::util::assign(rmq, sdsl::rmq_succinct_sct<>(&lcp));
}

bool Kangaroo::hamming_distance_threshold(int l, int k, int s1, int s2) {
    int i = s1; 
    int j = s2;
    int res = 0;
    int mis = 0;

    int max_i, max_j;

    if (i < n1){
        max_i = n1;
        max_j = n1 + n2;
    } else {
        max_i = n1 + n2;
        max_j = n2;
    }

    while (res <= l && mis <= k && i < max_i && j < max_j) {
        int tmp = 0;
        if (T[i] == T[j]) {
            if (csa.isa[i] > csa.isa[j])
                tmp = lcp[rmq(csa.isa[j]+1, csa.isa[i])];
            else
                tmp = lcp[rmq(csa.isa[i]+1, csa.isa[j])];
        }
        i = i + tmp + 1;
        j = j + tmp + 1;
        if (k == 0) return (res + tmp >= l);
        if (i >= max_i || j >= max_j) return (std::min(max_i - s1, max_j - s2) >= l);
        res = res + tmp + 1;
        mis++;
    }

    return (mis <= k && res >= l);
}


