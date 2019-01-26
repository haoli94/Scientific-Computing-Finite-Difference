//
// Created by haoli on 2018/12/2.
//

#ifndef FINAL_PROJECT_SPARSE_HPP
#define FINAL_PROJECT_SPARSE_HPP
#include <iostream>
#include <vector>
#include <string>
#include "COO2CSR.hpp"
#include "CGSolver.hpp"
class SparseMatrix{
    std::vector<int> row_id;
    std::vector<int> col_id;
    std::vector<double> val;
    int n_row;
    int n_col;
    bool transformed = false;


public:
    void add(int row,int col, double val);
    void COO2CSR();
    int CGsolve(std::vector<double> &b,std::vector<double> &x,double tol,std::string soln_file,std::string filename);

};
#endif //FINAL_PROJECT_SPARSE_HPP
