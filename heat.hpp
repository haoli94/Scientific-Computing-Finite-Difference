//
// Created by haoli on 2018/12/2.
//
#ifndef FINAL_PROJECT_HEAT_HPP
#define FINAL_PROJECT_HEAT_HPP
#include <iostream>
#include <vector>
#include <string>
#include "sparse.hpp"
#include "CGSolver.hpp"
#include "matvecops.hpp"
using namespace std;
class HeatEquation2D{
    SparseMatrix spa;
    vector<double> b,x;
    std::string filename;
    double l;
    double w;
    double h;
    double Tc;
    double Th;
    int n_rows;
    int n_cols;


public:
    HeatEquation2D(std::string& file);
    double Ti(int col_id);
    int solve(std::string soln_file);
    void reform_solution(std::string soln_file, int iter);

};
#endif //FINAL_PROJECT_HEAT_HPP
