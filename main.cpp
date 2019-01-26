#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "CGSolver.hpp"
#include "COO2CSR.hpp"
#include "sparse.hpp"
#include "heat.hpp"

using namespace std;


int main(int argc, char *argv[]){
    if (argc<2){
    cout << "Usage:" << endl;
    cout << "$ ./main input<#>.txt solution" << endl;
    }
    string input_file = argv[1];
    HeatEquation2D heat(input_file);
    string output_file = argv[2];
    int converged = heat.solve(output_file);
    if (converged!=1){
        cout<<"SUCCESS: CG solver converged in " << converged-1 << " iterations."<<endl;
    }else{
        cerr <<"CG solver did not converge"<<endl;
    }
    return 0;
}
