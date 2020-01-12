#include <iostream>
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

int nb_rep(10);

void execute_and_update_time(std::string name, double & runtime, int & res,
    std::function<int(std::vector<int> const& S1, std::vector<int> const& S2)> f,
    std::vector<int> const& S1, std::vector<int> const& S2)
{
    std::chrono::steady_clock sc;
    auto start = sc.now();

    res = f(S1, S2);

    auto end = sc.now();
    auto time_span = static_cast<std::chrono::duration<double>> (end - start);
    runtime = time_span.count();

    std::cout << name << " " << res << std::endl;
}

void compute_all(int k, double eps, std::function<std::vector<int>(int)> generate_string, std::string name_file, std::vector<int> list_length){
    std::ofstream outFile;
    outFile.open("data/" + name_file + "_" + std::to_string(k) + "_" + std::to_string(eps) + ".csv");
    if (outFile.is_open()) {
        std::vector<std::string> method_name{
            "dynprog",
            "LCSk-LSH",
        };

        std::map<std::string,std::function<int(std::vector<int> const& S1, std::vector<int> const& S2)>> method_function;
        method_function["dynprog"] = [k](std::vector<int> const& S1, std::vector<int> const& S2) -> int { return dynprog(S1, S2, k); };
        method_function["LCSk-LSH"] = [k, eps](std::vector<int> const& S1, std::vector<int> const& S2) -> int { return LCSk_LSH(k, eps, S1, S2); };

        outFile << "k,eps,length,L";
        for (auto const& name : method_name) {
            outFile << "," << name + "-time";
            outFile << "," << name + "-res";
        }
        outFile << std::endl;

        for (size_t i = 0; i < list_length.size(); i++) {
            double runtime(0);
            int res(0);

            std::cout << "Starting " << list_length[i] << "." << std::endl;
            for (int j = 0; j < nb_rep; j++) {
                std::cout << list_length[i] << ": Computation " <<  j << "..." << std::endl;
                std::vector<int> S1 = generate_string(list_length[i]);
                std::vector<int> S2 = generate_string(list_length[i]);

                outFile << k << "," << eps << "," << list_length[i] << "," << 6;//std::ceil(pow((double) list_length[i], (double) 1 / (1 + eps)) / log2(list_length[i]));
                for(auto const& name : method_name) {
                    execute_and_update_time(name, runtime, res, method_function[name], S1, S2);
                    outFile << "," << runtime;
                    outFile << "," << res;
                }
                outFile << std::endl;
            }
        }
    }
    else std::cout << "Unable to open files: " << name_file + ".csv " << std::endl;
}

void reg_random_eval(int k, double eps, int maxlength, int step, int alphabet) {
    std::vector<int> list_length;
    for (int i = step; i <= maxlength; i = i + step) {
        list_length.push_back(i);
    }

    auto generate_string = [alphabet](int l) -> std::vector<int> { return random_string(l, alphabet); };
    compute_all(k, eps, generate_string, "rand", list_length);
}

void reg_e_coli_eval(int k, double eps, int maxlength, int step) {
    std::vector<int> list_length;
    for (int i = step; i <= maxlength; i = i + step) {
        list_length.push_back(i);
    }

    auto generate_string = [](int l) -> std::vector<int> { return e_coli_string(l); };
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
    int k = 10;
    int alphabet = 4;
    int maxlength = 60000;
    int step = 5000;

    float eps = 1.0;
    reg_random_eval(k, eps, maxlength, step, alphabet);
    reg_e_coli_eval(k, eps, maxlength, step);

    eps = 1.5;
    reg_random_eval(k, eps, maxlength, step, alphabet);
    reg_e_coli_eval(k, eps, maxlength, step);

    eps = 2.0;
    reg_random_eval(k, eps, maxlength, step, alphabet);
    reg_e_coli_eval(k, eps, maxlength, step);

    return 0;
}
