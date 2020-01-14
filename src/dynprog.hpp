/**
 * \file dynprog.hpp
 * \brief Implementation of a dynamic programming algorithm of Flouri et al.
 * ``Longest common substrings with k mismatches.'' (2015), IPL.
 */
#pragma once

#include <vector>
#include <queue>

using namespace std;

/**
 * \brief  Dynamic programming algorithm for computing
 * the longest common substring with k mismatches.
 * \param   k max number of mismatches.
 * \param   S1 the first string (vector<int>).
 * \param   S2 the second string (vector<int>).
 * \return  The maximal length of a substring of S1 that occurs in S2
 * with at most k mismatches.
 */
int dynprog(vector<int> const& S1, vector<int> const& S2, int k);
