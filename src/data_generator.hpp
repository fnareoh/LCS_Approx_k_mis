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

using namespace std;

/**
 * \brief   Random string generator.
 * \param   l the length of a string to generate.
 * \param   alphabet the size of the alphabet.
 * \param   index = {1,2}
 * \return  A string of length l, where each character is selected
 * independently and uniformly at random from range.
 */
std::vector<int> random_string(int l, int alphabet, int index);

/**
 * \brief   Random string generator.
 * \param   l the length of a string to generate.
 * \param   index = {1,2}
 * \return  A string of length l, selected at random from
 * the E. coli genome.
 */
std::vector<int> e_coli_string(int l, int index);
