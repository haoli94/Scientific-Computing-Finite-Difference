#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include "COO2CSR.hpp"
#include "matvecops.hpp"
using namespace std;

std::string soln_name(std::string soln, int n_iter,std::string filename){
    stringstream ss;
    string soln_n;
    for(unsigned int i = 0;i < filename.size();i++){
        if(filename[i] >='0' && filename[i]<='9'){
            soln_n = filename[i];
        }
    }
    ss << std::setw(3) << std::setfill('0')<< n_iter;
    std::string s = soln;
    s += soln_n;
    s += ss.str();
    s += ".txt";
    cout<<s<<endl;
    return (string)s;
}
//puts the prefix and the iteration number that is be divisible by 10 and returns this solution file name

void soln_write(std::string filename,std::string soln, int n_iter,std::vector<double> &x){
    string new_filename = soln_name(soln,n_iter,filename);
    ofstream fout(new_filename);
    for (auto line:x){
        fout << line <<endl;
    }
    fout.close();
}
//writes the intermediate solutions out into a file

int CGSolver(std::vector<double> &val,
             std::vector<int>    &row_ptr,
             std::vector<int>    &col_idx,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol,
             std::string soln,
             std::string filename){
    int maxIterations = (int)x.size();
    //initialize the threshold to end the iteration.
    int iter = 0;
    //initialize the iteration times.
    vector<double> Au0 = matdotvec(row_ptr,col_idx,val,x);
    vector<double> r = deduction(b,Au0);
    //initialize the r0.
    vector<double> p = r;
    //initialize the p0.
    double L2norm0 = L2norm(r);
    //initialize the L2norm0
    soln_write(filename,soln,iter,x);
    while (iter < maxIterations){
        iter++;
        //current iteration time
        vector<double> ptA = matdotvec(row_ptr,col_idx,val,p);
        double rSquared = matrixProduct(r,r);
        //compute rnT*rn.
        double ptAP = matrixProduct(ptA,p);
        //compute pnT*A*pn.
        double alpha = rSquared / ptAP;
        //use rnT*rn and pnT*A*pn to compute alpha.
        vector<double> alphaP = scalaMultiple(p,alpha);
        //compute  alphan*pn .
        x = addition(x,alphaP);
        // update x
        vector<double> alphaAP = scalaMultiple(ptA,alpha);
        vector<double> rn = deduction(r,alphaAP);
        //compute new rn.
        double L2normn = L2norm(rn);
        double threshold = L2normn/L2norm0;
        if (threshold < tol){
            break;
            //break when the CG solver converges
        }
        if (iter%10==0)soln_write(filename,soln,iter,x);
        double rTr = matrixProduct(r,r);
        double rnTrn = matrixProduct(rn,rn);
        double beta = rnTrn / rTr;
        //compute beta
        vector<double> betaP = scalaMultiple(p,beta);
        p = addition(rn,betaP);
        //update p
        r = rn;
        //update r
    }
    soln_write(filename,soln,iter,x);
    if (iter<maxIterations) return iter;
    else return -1;
    //return the times of iteration when CG solver converges or the while loop ends.
}


