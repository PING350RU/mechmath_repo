#include "functions.h"

#include <algorithm>
#include <cmath>

using namespace std;

bool jordanInverse(int n, Matrix& a, Matrix& inverse) {
    for (int i = 0; i < n; i++) {
        inverse[i][i] = 1.0;
    }

    const double eps = 1e-15;

    for (int col = 0; col < n; col++) {
        int mainRow = col;

        for (int row = col + 1; row < n; row++) {
            if (abs(a[row][col]) > abs(a[mainRow][col])) {
                mainRow = row;
            }
        }

        if (abs(a[mainRow][col]) < eps) return false;

        swap(a[col], a[mainRow]);
        swap(inverse[col], inverse[mainRow]);

        double pivot = a[col][col];

        for (int j = col + 1; j < n; j++) {
            a[col][j] /= pivot;
        }
        a[col][col] = 1.0;

        for (int j = 0; j < n; j++) {
            inverse[col][j] /= pivot;
        }

        for (int row = 0; row < n; row++) {
            if (row == col) continue;

            double factor = a[row][col];
            if (factor == 0.0) continue;

            for (int j = col + 1; j < n; j++) {
                a[row][j] -= factor * a[col][j];
            }
            a[row][col] = 0.0;

            for (int j = 0; j < n; j++) {
                inverse[row][j] -= factor * inverse[col][j];
            }
        }
    }

    return true;
}
