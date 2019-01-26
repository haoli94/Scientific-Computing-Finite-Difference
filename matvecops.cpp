#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<double> addition(vector<double> &a,vector<double> &b){
    if (a.size() != b.size()) {
        cerr << "Error occurs that the two CSR  are not in the same size" << endl;
    }
    vector<double> vec;
    for (unsigned int i=0;i<a.size();i++){
        double add = a[i] + b[i];
        vec.push_back(add);
    }
    return vec;
}
//define the vector addition method.

vector<double> deduction(vector<double> &a, vector<double> &b){
    if (a.size() != b.size()) {
        cerr << "Error occurs that the two CSR  are not in the same size" << endl;
    }
    vector<double> vec;
    for (unsigned int i=0;i<a.size();i++){
        double d = a[i]-b[i];
        vec.push_back(d);
    }
    return vec;
}
//define the vector deduction method.

double matrixProduct(vector<double> &a,vector<double> &b) {
    if (a.size() != b.size()) {
        cerr << "Error occurs that the two CSR  are not in the same size" << endl;
    }
    double sum = 0;
    for (unsigned int i = 0; i < a.size(); i++) {
        sum += a[i] * b[i];
    }
    return sum;
}
//define the method that vector times a vector.

vector<double> scalaMultiple(vector<double> &a, double b){
    vector<double> scalar;
    for (unsigned int i=0;i<a.size();i++){
        double c = a[i] * b;
        scalar.push_back(c);
    }
    return scalar;
}
//define the method that vector times a scalar.

double L2norm(vector<double> &v1){
    double L2norm = 0;
    for (unsigned int i = 0; i < v1.size(); i++) {
        L2norm += v1[i]*v1[i];
    }
    return sqrt(L2norm);
}
//define the method to compute the norm of a vector.

vector<double> matdotvec(vector<int> &row_numbers,vector<int> &col_numbers,
                         vector<double> &values,vector<double> &u){
    vector<double> Au;
    for (unsigned int i=0;i<row_numbers.size()-1;i++){
        double sum = 0;
        for (int j=row_numbers[i];j<row_numbers[i+1];j++){
            sum += values[j]* u[col_numbers[j]];
        }
        Au.push_back(sum);
    }
    return Au;
}
//define the method that a CSR matrix times a vector.
