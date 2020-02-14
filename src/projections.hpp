/**
 * \file projections.hpp
 * \brief Definitions of projections and collision sets.
 */

#pragma once

#include <algorithm>
#include <cassert> 
#include <random>
#include <string>
#include <vector>

using namespace std;

/**
 * \brief  Represent a single projection.
 *
 * \section Role
 *   A projection is a sorted vector of positions on which a string can be
 *   projected.
 *
 * \section Behaviour
 *   A projection is a vector of position and an integer l, the
 *   length of the substring you project.
 *   Methods: construct, evaluate a projection on a string
 *   and decide whether we project onto a given position.
 */
class Projection {
public:
    int n; ///< Length of the substring being projected.
    int l; ///< Length we limit ourselves to.
    vector<int> positions; ///< vector of positions.

    /**
    * \brief  Create a projection.
    * \param  m the number of positions we project onto.
    * \param  n the range of positions.
    * \param  len the range among which the positions will be saved.
    */
    Projection(int m, int n, int len);
};

/**
 * \brief  Represent a single collision.
 *
 * \section Role
 *   A collision is a pair of l-length substrings of strings S1,S2
 *   such that their projections are equal.
 *
 * \section Behaviour
 *   A collision is represented by the starting positions of the 
 *   substrings in S1, S2 and a reference to the projection.
 */
class Collision {
public:
    int first_string; ///< starting position of the substring in S1.
    int second_string; ///< starting position of the substring in S2.
    Projection &h;  ///< projection for which the two substrings collide.

    /**
    * \brief  Create a collision.
    * \param  i the starting position of the substring in S1.
    * \param  j the starting position of the substring in S2.
    * \param  h the projection.
    */
    Collision(int i, int j, Projection &h);
    Collision& operator = (const Collision &other);
};

/**
 * \brief  Represent a set of collisions.
 *
 * \section Role
 *   Represent a set of collisions, is initialized as empty and collisions can be
 *   added, a single random_collision is also stored.
 *
 * \section Behaviour
 *   Enables access to the collisions and creation of new colisions.
 */
class CollisionSet {
public:
    vector<Collision> collisions; ///< The set of collisions.
    vector<Collision> random_collision; ///< A random collision, normaly there shoud be at most one.

    CollisionSet();
    void add_collision(Collision);
};

/**
 * \brief  Represent a set of projections.
 *
 * \section Behaviour
 *   Is initialized by creating L projections of m positions between 0 and len.
 */
class ProjectionSet {
public:
    int l; ///< range of the positions.
    vector<Projection> projections; ///< set of projections

    /**
    * \brief  Create a projections set.
    * \param  L the number of projections.
    * \param  m the number of positions we project onto.
    * \param  n the range of positions.
    * \param  len the range among which the positions will be saved.
    */
    ProjectionSet(int L, int m, int n, int len);
};
