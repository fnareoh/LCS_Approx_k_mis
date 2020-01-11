/**
 * \file decision.hpp
 * \brief Decision verision of LCS_k.
 */

#pragma once

#include <cassert>
#include <vector>
#include <iostream>
#include <functional>

#include "projections.hpp"
#include "collisions.hpp"

/**
* \brief Solves the decision variant of LCS_k.
* \param  l the threshold length.
* \param  k the max number of mismatches.
* \param  1 + eps the approximation factor.
* \param  S1 the first string.
* \param  S2 the second string.
* \return true if there is a substring of length l in S1 and S2 such
* that the two are at distance less than (1+eps)*k, else false.
*/
bool LCSk_LSH_decision(int l, int k, double eps,
    std::vector<int> const&, std::vector<int> const&);
