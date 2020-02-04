/**
 * \file NTT.hpp
 * \brief Computing the convolution of two integer vectors.
 */

#pragma once

#include <algorithm>
#include <vector>

using namespace std;

/**
 * \brief Computing the convolution of two integer vectors.
 * \param A the first vector
 * \param B the second vector
 * \return the convolution of A and B
 */ 
vector<unsigned> conv(vector<unsigned> A, vector<unsigned> B);
