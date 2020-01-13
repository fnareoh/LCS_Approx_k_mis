/**
 * \file data_generator.hpp
 * \brief Generate the data for the experiments.
 */

#pragma once

#include <random>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <cassert>
#include <ctime>

/**
 * \brief   Random string generator.
 * \param   length the length of a string to generate.
 * \param   alphabet the size of the alphabet.
 * \param   S2 the second string (vector<int>).
 * \return  A string of length length, where each character is selected
 * independently and uniformly at random from range.
 */
std::vector<int> random_string(long long int length, int alphabet);

std::vector<int> e_coli_string(long long int l);
