#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <stdlib.h>

#include "20q.hpp"
#include "dynprog.hpp"
#include "data_generator.hpp"

using namespace std;

int nb_rep(10);

void execute_and_update_time(string name, double & runtime, int & res,
    function<int(vector<int> const& S1, vector<int> const& S2)> f,
    vector<int> const& S1, std::vector<int> const& S2)
{
    chrono::steady_clock sc;
    auto start = sc.now();

    res = f(S1, S2);

    auto end = sc.now();
    auto time_span = static_cast<chrono::duration<double>> (end - start);
    runtime = time_span.count();

    cout << name << " " << res << endl;
}

void compute_all(int k, double eps, function<vector<int>(int, int)> generate_string, string name_file, vector<int> list_length){
    ofstream outFile;
    outFile.open("data/" + name_file + "_" + std::to_string(k) + "_" + std::to_string(eps) + ".csv");
    if (outFile.is_open()) {
        vector<string> method_name{
            "dynprog",
            "LCSk-LSH",
        };

        map<string,function<int(vector<int> const& S1, vector<int> const& S2)>> method_function;
        method_function["dynprog"] = [k](vector<int> const& S1, vector<int> const& S2) -> int { return dynprog(S1, S2, k); };
        method_function["LCSk-LSH"] = [k, eps](vector<int> const& S1, vector<int> const& S2) -> int { return LCSk_LSH(k, eps, S1, S2); };

        outFile << "k,eps,length,L";
        for (auto const& name : method_name) {
            outFile << "," << name + "-time";
            outFile << "," << name + "-res";
        }
        outFile << endl;

        for (size_t i = 0; i < list_length.size(); i++) {
            double runtime(0);
            int res(0);

            cout << "Starting " << list_length[i] << "." << endl;
            for (int j = 0; j < nb_rep; j++) {
                cout << list_length[i] << ": Computation " <<  j << "..." << endl;
                vector<int> S1 = generate_string(list_length[i], 1);
                vector<int> S2 = generate_string(list_length[i], 2);

                outFile << k << "," << eps << "," << list_length[i] << "," << ceil(pow((double) list_length[i], (double) 1 / (1 + eps)) / 16);
                for(auto const& name : method_name) {
                    execute_and_update_time(name, runtime, res, method_function[name], S1, S2);
                    outFile << "," << runtime;
                    outFile << "," << res;
                }
                outFile << endl;
            }
        }
    }
    else cout << "Unable to open files: " << name_file + ".csv " << endl;
}

void random_eval(int k, double eps, int maxlength, int step, int alphabet) {
    vector<int> list_length;
    for (int i = step; i <= maxlength; i = i + step) {
        list_length.push_back(i);
    }

    auto generate_string = [alphabet](int l, int index) -> vector<int> { return random_string(l, alphabet, index); };
    compute_all(k, eps, generate_string, "random", list_length);
}

void e_coli_eval(int k, double eps, int maxlength, int step) {
    vector<int> list_length;
    for (int i = step; i <= maxlength; i = i + step) {
        list_length.push_back(i);
    }

    auto generate_string = [](int l, int index) -> vector<int> { return e_coli_string(l, index); };
    compute_all(k, eps, generate_string, "e_coli", list_length);
}

/*int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " k eps maxlength step alphabet" << std::endl;
        return 1;
    }
    int k = atoi(argv[1]);
    double eps = atof(argv[2]);  
    int maxlength = atoi(argv[3]);
    int step = atoi(argv[4]);
    int alphabet = atoi(argv[5]);*/

int main() {
    int alphabet = 4;
    int maxlength = 60000;
    int step = 5000;
    int k = 50;

    float eps = 1.0;
    random_eval(k, eps, maxlength, step, alphabet);
    e_coli_eval(k, eps, maxlength, step);

    eps = 1.5;
    random_eval(k, eps, maxlength, step, alphabet);
    e_coli_eval(k, eps, maxlength, step);

    eps = 2.0;
    random_eval(k, eps, maxlength, step, alphabet);
    e_coli_eval(k, eps, maxlength, step);

    return 0;
}
