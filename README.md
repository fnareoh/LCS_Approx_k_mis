Longest Common Substring with Approximately k mismatches
===================================

The Longest Common Substring (LCS) is a classical problem where we aim at computing the maximum-length substring that occurs both in <img src="/tex/cbfb1b2a33b28eab8a3e59464768e810.svg?invert_in_darkmode&sanitize=true" align=middle width=14.908688849999992pt height=22.465723500000017pt/> and <img src="/tex/91aac9730317276af725abd8cef04ca9.svg?invert_in_darkmode&sanitize=true" align=middle width=13.19638649999999pt height=22.465723500000017pt/>. The LCS can be used as a similarity measure but its major disadvantage is that it is not robust to changes. The LCS between <img src="/tex/baceed79a810937f25669a38bc249b78.svg?invert_in_darkmode&sanitize=true" align=middle width=80.37676844999999pt height=26.76175259999998pt/> and <img src="/tex/7828e5be3e33324a8294d47fe5420ab7.svg?invert_in_darkmode&sanitize=true" align=middle width=34.78325729999999pt height=26.76175259999998pt/> is twice the size of the LCS between <img src="/tex/5835914f97c618a21aa88d6b6d370f39.svg?invert_in_darkmode&sanitize=true" align=middle width=83.69872994999999pt height=22.831056599999986pt/> and <img src="/tex/7828e5be3e33324a8294d47fe5420ab7.svg?invert_in_darkmode&sanitize=true" align=middle width=34.78325729999999pt height=26.76175259999998pt/>, even though only one character changed.
To remedy this problem, we can introduce a given number mismatches allowed in the longest substring. As such, the Longest Common Substring with <img src="/tex/63bb9849783d01d91403bc9a5fea12a2.svg?invert_in_darkmode&sanitize=true" align=middle width=9.075367949999992pt height=22.831056599999986pt/> mismatches problem offers a more robust solution. However, Kociumaka, Radoszewski and Starikovskaya [showed](https://arxiv.org/abs/1712.08573) that there is <img src="/tex/99d8e3f5a92262980afcd1f99d4422bc.svg?invert_in_darkmode&sanitize=true" align=middle width=90.40330529999999pt height=24.65753399999998pt/> such that the LCS with <img src="/tex/63bb9849783d01d91403bc9a5fea12a2.svg?invert_in_darkmode&sanitize=true" align=middle width=9.075367949999992pt height=22.831056599999986pt/> Mismatches problem cannot be solved in strongly subquadratic time, when a commonly believed hypothesis is true. Thus they introduced LCS with Approximately <img src="/tex/63bb9849783d01d91403bc9a5fea12a2.svg?invert_in_darkmode&sanitize=true" align=middle width=9.075367949999992pt height=22.831056599999986pt/> Mismatches: given <img src="/tex/63bb9849783d01d91403bc9a5fea12a2.svg?invert_in_darkmode&sanitize=true" align=middle width=9.075367949999992pt height=22.831056599999986pt/> and <img src="/tex/9ae7733dac2b7b4470696ed36239b676.svg?invert_in_darkmode&sanitize=true" align=middle width=7.66550399999999pt height=14.15524440000002pt/>, find a substring at Hamming distance less than <img src="/tex/926eddfe56693933f52dab9698fadc70.svg?invert_in_darkmode&sanitize=true" align=middle width=57.83670584999999pt height=24.65753399999998pt/> and of length at least the <img src="/tex/6a5addc9341bb1efb2869382176d9a42.svg?invert_in_darkmode&sanitize=true" align=middle width=38.54463194999999pt height=22.465723500000017pt/>. 


This repository contains an implementation of a newly designed solution to this problem.

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