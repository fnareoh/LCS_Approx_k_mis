/**
 * \file 20q.hpp
 * \brief Allows to solve LCS with approx. k mismatches 
 * using and algorithm for the decision version of the problem.
*/
#pragma once

#include <stack>
#include <cassert>

#include "decision.hpp"

using namespace std;

/**
* \brief  Solves LCS with approximately k mismatches via the Twenty Questions game.
* \param  k the max number of mismatches.
* \param  1 + eps the approximation factor.
* \param  S1 the first string.
* \param  S2 the second string.
* \return true if there is a substring of length l in S1 and S2 such
* that the two are at distance less than (1+eps)*k, else false.
*/
long long int LCSk_LSH_20q(int k, double eps, vector<int> const& S1, vector<int> const& S2);
