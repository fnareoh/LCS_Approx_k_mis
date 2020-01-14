#include "data_generator.hpp"

vector<int> filter_dna(){
  vector<int> T;
  ifstream dna("data/e_coli.fasta", ios::in);
  map<char, char> dna_map = {
    { 'A', 0 },
    { 'C', 1 },
    { 'G', 2 },
    { 'T', 3 },
    { 'N', 4 }
  };
  if (dna)
  {
    string t((istreambuf_iterator<char>(dna)),
    istreambuf_iterator<char>());
    t.erase(remove(t.begin(), t.end(), '\n'), t.end());
    for(int i = 0; i < t.size();i++){
      if (t[i] == 'A' || t[i] == 'C' || t[i] == 'G' || t[i] == 'T' || t[i] == 'N'){
        T.push_back(dna_map[t[i]]);
      }
    }
    dna.close();
  }
  else cout << "Can't open e_coli.fasta file" << std::endl;
  return T;
}

vector<int> e_coli_string(int l, int index){
    vector<int> dna = filter_dna();
    assert(dna.size() >= 2 * l);
    vector<int>::const_iterator first = dna.begin() + rand() % (dna.size() / 2 - l) + (index - 1) * dna.size() / 2;
    vector<int>::const_iterator last =  first + l;
    vector<int> newVec(first, last);
    return newVec;
}

vector<int> random_string(int l, int alphabet, int index){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, alphabet - 1);

    vector<int> S(l, 0);
    for (long long int i = 0; i < l; i++) {
        S[i] = dis(gen);
    }
    return S;
}
