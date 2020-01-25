Longest Common Substring with Approximately k mismatches
===================================

Assume that we are given two strings, X and Y, and must understand how similar they are. The Longest Common Substring (LCS) is a classical problem where we aim at computing the maximum-length substring that occurs both in X and Y. The LCS can be used as a similarity measure but its major disadvantage is that it is not robust to changes. To remedy this problem, we can introduce a fixed number of mismatches allowed in the longest substring, k. As such, the Longest Common Substring with k mismatches problem offers a more robust solution. However, Kociumaka, Radoszewski and Starikovskaya [showed](https://arxiv.org/abs/1712.08573) that the LCS with k Mismatches problem cannot be solved in strongly subquadratic time, when a commonly believed hypothesis is true. Thus they introduced LCS with Approximately k Mismatches. This repository contains an implementation of a newly designed solution to this problem.

Compilation
===================================

This project is written in C++ 11 for the implementation of the solutions and Python 3 to plot the graphs of time analysis. The plot module depends on `matplotlib`.

To install the repository:

```sh
git clone git@github.com:fnareoh/LCS_Approx_k_mis.git
cd kApproxLCS
```
```sh
make all
```