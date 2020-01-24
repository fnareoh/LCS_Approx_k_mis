/**
 * \file kangaroo.hpp
 * \brief Data structures for kangaroo jumps
 */
#pragma once

#include <string>
#include <vector>

#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include <sdsl/rmq_support.hpp>
#include <sdsl/util.hpp>

/**
 * \brief Structure to compute kangaroo jumps.
 *
 * \section Behaviour
 *   Just several sdsl-lite structures augmented with an operation for kangaroo
 *   jumps : hamming_distance_threshold
 */
class Kangaroo {
    public:
        int n1;
        int n2;
        std::vector<int> T;

        sdsl::csa_bitcompressed<> csa;
        sdsl::lcp_bitcompressed<> lcp;
        sdsl::rmq_succinct_sct<> rmq;

        Kangaroo();
        void construct(std::vector<int> const&, std::vector<int> const&);
        bool is_lower(int i, int j);

        //int l, k, s1, s2
        /**
        * \brief  Computes the longest common prefix with k mismatches
        * \param  k number of mismatches authorized
        * \param  s1, s2 starting positions in the input string
        * \param  l threshold length
        * \return true if the length of the longest common prefix with k mismatches
        * of the suffixes starting at positions s1, s2 is at least l
        */
        int hamming_distance_threshold(int, int, int, int);
};
