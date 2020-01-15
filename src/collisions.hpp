/**
 * \file collisions.hpp
 * \brief Generate a set of collisions to be tested
 * for a given set of projections.
 */

#pragma once

#include <algorithm> 
#include <cassert> 
#include <random> 
#include <utility> 

#include "projections.hpp"
#include "NTT.hpp"

using namespace std;

/**
 * \brief   Computes the collisions of all l-length substrings of two strings.
 * \param   H the projection set.
 * \param   S1 the first string (vector<int>).
 * \param   S2 the second string (vector<int>).
 * \return  The resulting collision set.
 */
CollisionSet generate_collisions(ProjectionSet H, vector<int> const& S1, vector<int> const& S2);

