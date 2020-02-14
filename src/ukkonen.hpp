/**
 * \file ukkonen.hpp
 * \brief Suffix tree construction via Ukkonen's algorithm.
 */

#pragma once

#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const bool USE_SUFFIX_TREE = true;

struct STedge;

/**
 * \brief  Represent a node of the suffix tree.
 *
 * \section Role
 *   A node of the suffix tree stores edges to its children.
 *
 * \section Behaviour
 *   A node of the suffix tree stores a map g of edges to its children,
 *   a suffix link f and an integer leaf_no that indicates, if the label of the
 *   node is a suffix of the underlying text, the index of the suffix.
 */
struct STvertex {
    map<int, STedge> g;
    STvertex *f;
    /* suffix number (-1 means that the node is not a leaf) */
    int leaf_no;
};

/**
 * \brief  Represent an edge of the suffix tree.
 *
 * \section Role
 *   An edge of the suffix tree is labeled by a substring of the text.
 *
 * \section Behaviour
 *   An edge of the suffix tree stores, as integers l and r, the endpoints of
 *   the text substrings that it represents, as well as the suffix tree node v
 *   being its bottom endpoint.
 */
struct STedge {
    int l, r; /* x[l]..x[r] is the text fragment representing an edge */
    STvertex *v;
};

class SuffixTree {
private:
    vector<int> *txt;
    int n;
    STvertex *root;
    int num_leaves;
    vector<int> SA, RANK, LCP;
    vector<vector<int> > DBF;

public:
    /**
    * \brief  Create the suffix tree of a text.
    * \param  x the text; should end with a sentinel (negative number).
    * \param  _n text length.
    */
    void Create_suffix_tree(vector<int> *x, int _n);

    /**
    * \brief  Delete the suffix tree from memory.
    */
    void Delete_suffix_tree();

    /**
    * \brief  Compute the longest common substring of two strings T_1 and T_2.
    * \param  pos1 position of -2 in the text T_1 (-2) T_2 (-1)
    * \param  pos2 position of -1 in the text T_1 (-2) T_2 (-1)
    * \return The length of the longest common substring.
    */
    int LCS(int pos1, int pos2);

    /**
    * \brief  Create the suffix arrays of the text.
    */
    void Compute_suffix_arrays();

    /**
    * \brief  Compute the longest common extension.
    * \param  i index in the text
    * \param  j index in the text
    * \return The length of the longest common prefix of T[i..] and T[j..].
    */
    int LCE(int i, int j);

private:
    inline void Canonize(STedge &edge, vector<int> *x);

    inline bool Test_and_split(STvertex* &w, const STedge &edge);

    void Update(STedge &edge);
    
    void STDelete(STvertex *w);
    
    int LCS_recurse(STvertex *w, int depth, int pos1, int pos2, int &lcs);

    void SA_recurse(STvertex *w, int depth, int &top_node);

    void Compute_RMQ();
};
