/* Suffix tree construction via Ukkonen's algorithm */
#pragma once

#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const bool USE_SUFFIX_TREE = true;

struct STedge;

struct STvertex {
  map<int, STedge> g; /* edges to children */
  STvertex *f; /* suffix link */
  /* suffix number (-1 means that the node is not a leaf) */
  int leaf_no;
};

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
  /* x should end with a sentinel, e.g. -1 */
  void Create_suffix_tree(vector<int> *x, int _n);

  void Delete_suffix_tree();

  int LCS(int pos1, int pos2);

  void Compute_suffix_arrays();

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
