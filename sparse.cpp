//
// Created by haoli on 2018/12/2.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "sparse.hpp"
#include "COO2CSR.hpp"
#include "CGSolver.hpp"


using namespace std;


void SparseMatrix::add(int row,int col, double val){
    if (this->transformed){
        cerr<<"it's already in CSR form,can not add entries with COO forms!"<<endl;
    }else{
        this->col_id.push_back(col);
        this->row_id.push_back(row);
        this->val.push_back(val);
	//store the data in COO format
    }
}

void SparseMatrix::COO2CSR(){
    if (this->transformed)return;
    ::COO2CSR(this->val, this->row_id, this->col_id);
    this->transformed = true;
    //transform the COO matrix to CSR matrix
}


int SparseMatrix::CGsolve(std::vector<double> &b,std::vector<double> &x,double tol,std::string soln_file,std::string filename){
    int n_iter = ::CGSolver(this->val,this->row_id,this->col_id,b,x,tol,soln_file,filename);
    return n_iter;
    //call the CGSolver defined earlier and return the number of total iterations
}
