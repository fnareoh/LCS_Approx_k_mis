#include "ukkonen.hpp"

void SuffixTree::Create_suffix_tree(vector<int> *x, int _n) {
  STvertex *top;
  STedge e;
  top = new STvertex;
  root = new STvertex;
  txt = x;
  n = _n;
  top->leaf_no = root->leaf_no = -1;
  e.v = root; num_leaves = 0;
  for (int i = 0; i < n; ++i) {
    e.r = -i;
    e.l = -i;
    top->g[(*x)[i]] = e;
  }
  root->f = top;
  e.l = 0; e.v = root;
  for (int i = 0; i < n; ++i) {
    e.r = i - 1;
    Update(e); 
    ++e.r;
    Canonize(e, x);
  }
}

inline void SuffixTree::Canonize(STedge &edge, vector<int> *x) {
  if (edge.l <= edge.r) {
    STedge e = edge.v->g[(*x)[edge.l]];
    while (e.r - e.l <= edge.r - edge.l) {
      edge.l += e.r - e.l + 1;
      edge.v = e.v;
      if (edge.l <= edge.r) e = edge.v->g[(*x)[edge.l]];
    }
  }
}

inline bool SuffixTree::Test_and_split(STvertex* &w, const STedge &edge) {
  w = edge.v;
  if (edge.l <= edge.r) {
    int c = (*txt)[edge.l];
    STedge e = edge.v->g[c];
    if ((*txt)[edge.r + 1] == (*txt)[e.l + edge.r - edge.l + 1]) return true;
    w = new STvertex; w->leaf_no = -1;
    edge.v->g[c].r = e.l + edge.r - edge.l;
    edge.v->g[c].v = w;
    e.l += edge.r - edge.l + 1;
    w->g[(*txt)[e.l]] = e;
    return false;
  }
  return edge.v->g.find((*txt)[edge.l]) != edge.v->g.end();
}

void SuffixTree::Update(STedge &edge) {
  STvertex *oldr = root, *w;
  while (!Test_and_split(w, edge)) {
    STedge e;
    e.v = new STvertex;
    e.l = edge.r + 1; e.r = n - 1;
    e.v->leaf_no = num_leaves++;
    w->g[(*txt)[edge.r + 1]] = e;
    if (oldr != root) oldr->f = w;
    oldr = w;
    edge.v = edge.v->f;
    Canonize(edge, txt);
  }
  if (oldr != root) oldr->f = edge.v;
}

void SuffixTree::STDelete(STvertex *w) {
  for (map<int, STedge>::iterator it = w->g.begin(); it != w->g.end(); ++it)
    STDelete(it->second.v);
  delete w;
}

void SuffixTree::Delete_suffix_tree() {
  STDelete(root);
  SA.clear(); RANK.clear(); LCP.clear(); DBF.clear();
}

int SuffixTree::LCS_recurse(STvertex *w, int depth, int pos1, int pos2, int &lcs) {
  int mask = 0;
  for (map<int, STedge>::iterator it = w->g.begin(); it != w->g.end(); ++it) {
    STedge e = (*it).second;
    int mask1 = LCS_recurse(e.v, depth + e.r - e.l + 1, pos1, pos2, lcs);
    if (e.l <= pos1 && pos1 <= e.r) mask |= 1;
    else if (mask1 & 2) mask |= 2;
    if (mask1 & 1) mask |= 1;
    if (pos1 < e.l && e.r == pos2) mask |= 2;
  }
  if (mask == 3) lcs = max(lcs, depth);
  return mask;
}

int SuffixTree::LCS(int pos1, int pos2) {
  int lcs = 0;
  LCS_recurse(root, 0, pos1, pos2, lcs);
  return lcs;
}

void SuffixTree::SA_recurse(STvertex *w, int depth, int &top_node) {
  if (w->leaf_no != -1) {
    SA.push_back(w->leaf_no);
    if ((int)SA.size() > 1)
      LCP.push_back(top_node);
    top_node = depth;
  } else {
    for (map<int, STedge>::iterator it = w->g.begin(); it != w->g.end(); ++it) {
      STedge e = (*it).second;
      SA_recurse(e.v, depth + e.r - e.l + 1, top_node);
      top_node = min(top_node, depth);
    }
  }
}

void SuffixTree::Compute_RMQ() {
  DBF.push_back(vector<int>());
  for (int i = 0; i < n - 1; ++i)
    DBF[0].push_back(LCP[i]);
  for (int j = 1; (1 << j) <= n - 1; ++j) {
    DBF.push_back(vector<int>());
    for (int i = 0; i < n - 1 - (1 << j) + 1; ++i)
      DBF[j].push_back(min(DBF[j - 1][i], DBF[j - 1][i + (1 << (j - 1))]));
  }
}

void SuffixTree::Compute_suffix_arrays() {
  int top_node;
  SA_recurse(root, 0, top_node);
  RANK.resize(n);
  for (int i = 0; i < n; ++i) {
    RANK[SA[i]] = i;
  }
  Compute_RMQ();
}

int SuffixTree::LCE(int i, int j) {
  if (i == j) return n - i;
  int i1 = RANK[i], j1 = RANK[j];
  if (i1 > j1) swap(i1, j1);
  int level = 8 * sizeof(int) - 1 - __builtin_clz(j1 - i1);
  return min(DBF[level][i1], DBF[level][j1 - (1 << level)]);
}
