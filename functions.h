#pragma once

#include <vector>

using namespace std;

using Matrix = vector<vector<double>>;

double formula(int k, int n, int i, int j);
bool initMatrix(int n, int k, const char* filename, Matrix& a);
bool jordanInverse(int n, Matrix& a, Matrix& inverse);
void printMatrix(const Matrix& a, int rows, int cols, int m);
double residualNorm(const Matrix& a, const Matrix& inverse);
