//
// Created by haoli on 2018/12/2.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <ios>
#include "heat.hpp"
using namespace std;

HeatEquation2D::HeatEquation2D(std::string& file) {
    this->filename = file;
    ifstream fin;
    fin.open(this->filename);
    if (fin.fail()) {
        cerr << "Error occurs when reading the file" << endl;
    }
    fin >> this->l >> this->w >> this->h;
    fin >> this->Tc >> this->Th;
    fin.close();
    this->n_rows = (int) (w / h) - 1;
    this->n_cols = (int) (l / h);
    this->x.resize((unsigned int) this->n_rows * this->n_cols, 1.);
    for (int r = 0; r < this->n_rows; r++) {
        for (int c = 0; c < this->n_cols; c++) {
            int centroid = c + this->n_cols * r;
            int left = (c + n_cols - 1) % n_cols + this->n_cols * r;
            int right = (c + n_cols + 1) % n_cols + this->n_cols * r;
            int upward = c + this->n_cols * (r + 1);
            int downward = c + this->n_cols * (r - 1);
            this->spa.add(centroid, centroid, 4);
            this->spa.add(centroid, left, -1);
            this->spa.add(centroid, right, -1);
            if (r == 0) {
                this->b.push_back(HeatEquation2D::Ti(c));
            } else {
                this->spa.add(centroid, downward, -1);
            }
            if (r == n_rows - 1) {
                this->b.push_back(this->Th);
            } else {
                this->spa.add(centroid, upward, -1);
            }
            if (r != 0 and r != n_rows - 1){
                this->b.push_back(0.);
            }
        }
    }
}

//initialize the HeatEquation2D class and construct the heat equation in COO matrix, 
//if the point is on the top and bottom border, I put them in the solution b, otherwise, I push back -1 into A.

double HeatEquation2D::Ti(int col_id){
	double Ti = -Tc*(exp(-10*(col_id-(n_cols)/2.)*h*(col_id-(n_cols)/2.)*h)-2);
	return Ti;
}
//calculate the temperature on the bottom line

int HeatEquation2D::solve(std::string soln_file){
    spa.COO2CSR();
    int converged = 0;
    double tol = 1e-5;
    int iter = spa.CGsolve(this->b,this->x,tol,soln_file,this->filename);
    if (iter != -1)converged = 1;
    HeatEquation2D::reform_solution(soln_file,iter);
    return converged+iter;
}
//transform the COO matrix to CSR format and call the CGSolve to solve the matrix return the iteration numbers
void  HeatEquation2D::reform_solution(std::string soln_file, int iter){
    vector<int> soln_numbers;
    for (int start = 0;start<iter;start+=10) {
        soln_numbers.push_back(start);
    }
    soln_numbers.push_back(iter);
    //get the results file numbers that we are going to report
    for (auto i = soln_numbers.begin(); i < soln_numbers.end(); ++i) {
        double sol;
        vector<double> solns;
        stringstream sout;
        sout << std::setw(3) << std::setfill('0')<< *i;
        std::string stringout = soln_file;
        string soln_n;
        for(auto i = this->filename.begin();i < this->filename.end();i++){
            if(*i >='0' && *i<='9'){
                soln_n = *i;
            }
        }
        stringout += soln_n;
        stringout += sout.str();
        stringout += ".txt";
        //get the output filename
        ifstream fin(stringout);
        while (fin>>sol){
            solns.push_back(sol);
        }
        fin.close();
//        ofstream fout(stringout);
        ofstream fout(stringout,ios::trunc);
        fout<<this->n_rows<<" "<<n_cols<<endl;
        for(int t=0;t<this->n_cols;t++){
            fout<<HeatEquation2D::Ti(t)<<endl;;
        }
        for(auto z = solns.begin();z < solns.end();z++){
            fout<<*z<<endl;;
        }

        for(int m=0;m<this->n_cols;m++){
            fout<<Th<<endl;;
        }
        fout.close();
    }

}
//add the bottom and top temperature line back to the solution.
