
#ifndef FINAL_PROJECT_MATVECOPS_HPP
#define FINAL_PROJECT_MATVECOPS_HPP
#include <vector>
using namespace std;

vector<double> addition(vector<double> &a,vector<double> &b);

vector<double> deduction(vector<double> &a, vector<double> &b);

double matrixProduct(vector<double> &a,vector<double> &b);

vector<double> scalaMultiple(vector<double> &a, double b);

double L2norm(vector<double> &v1);

vector<double> matdotvec(vector<int> &row_numbers,vector<int> &col_numbers,
                         vector<double> &values,vector<double> &u);

#endif //FINAL_PROJECT_MATVECOPS_HPP
