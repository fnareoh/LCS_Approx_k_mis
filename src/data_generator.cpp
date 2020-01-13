#include "data_generator.hpp"

std::vector<int> filter_dna(){
  std::vector<int> T;
  std::ifstream dna("data/sequence.fasta", std::ios::in);
  std::map<char, char> dna_map = {
    { 'A', 0 },
    { 'C', 1 },
    { 'G', 2 },
    { 'T', 3 },
    { 'N', 4 }
  };
  if (dna)
  {
    std::string t((std::istreambuf_iterator<char>(dna)),
    std::istreambuf_iterator<char>());
    t.erase(std::remove(t.begin(), t.end(), '\n'), t.end());
    for(int i = 0; i < t.size();i++){
      if (t[i] == 'A' || t[i] == 'C' || t[i] == 'G' || t[i] == 'T' || t[i] == 'N'){
        T.push_back(dna_map[t[i]]);
      }
    }
    dna.close();
  }
  else std::cout << "Can't open sequence.fasta file" << std::endl;
  return T;
}

std::vector<int> e_coli_string(long long int l){
	std::vector<int> dna = filter_dna();
    assert(dna.size()>=l);
    std::srand(unsigned(std::time(0)));
    std::vector<int>::const_iterator first = dna.begin() + rand() % (dna.size()-l);
    std::vector<int>::const_iterator last =  first + l;
    std::vector<int> newVec(first, last);
    return newVec;
}

std::vector<int> random_string(long long int length, int alphabet){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, alphabet - 1);

    std::vector<int> S(length, 0);
     for (long long int i = 0; i < length; i++) {
         S[i] = dis(gen);
     }
     return S;
}
