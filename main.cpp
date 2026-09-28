#include "functions.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

bool readInt(const char* text, int& value) {
    try {
        size_t pos = 0;
        value = stoi(text, &pos);
        return text[pos] == '\0';
    } catch (...) {
        return false;
    }
}

void printMatrix(const Matrix& a, int rows, int cols, int m) {
    for (int i = 0; i < min(rows, m); i++) {
        for (int j = 0; j < min(cols, m); j++) {
            printf(" %10.3e", a[i][j]);
        }
        printf("\n");
    }
}

double residualNorm(const Matrix& a, const Matrix& inverse) {
    int n = static_cast<int>(a.size());
    vector<double> row(n);
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        fill(row.begin(), row.end(), 0.0);

        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                row[j] += a[i][k] * inverse[k][j];
            }
        }

        for (int j = 0; j < n; j++) {
            double diff = row[j] - (i == j ? 1.0 : 0.0);
            result += diff * diff;
        }
    }

    return sqrt(result);
}

int main(int argc, char* argv[]) {
    int n, m, k;

    if (argc < 4 || argc > 5 ||
        !readInt(argv[1], n) || !readInt(argv[2], m) || !readInt(argv[3], k) ||
        n <= 0 || m <= 0 || k < 0 || k > 4 ||
        (k == 0 && argc != 5) || (k != 0 && argc != 4)) {
        cerr << "Использование: jordan n m k [filename], k = 0..4\n";
        return 1;
    }

    const char* filename = k == 0 ? argv[4] : nullptr;
    Matrix a(n, vector<double>(n, 0.0));
    Matrix inverse(n, vector<double>(n, 0.0));

    if (!initMatrix(n, k, filename, a)) {
        cerr << "ошибка\n";
        return 1;
    }

    printf("Матрица A:\n");
    printMatrix(a, n, n, m);

    auto start = chrono::steady_clock::now();
    bool ok = jordanInverse(n, a, inverse);
    auto finish = chrono::steady_clock::now();
    double seconds = chrono::duration<double>(finish - start).count();

    if (!ok) {
        cerr << "Ошибка: матрица вырождена\n";
        return 2;
    }

    printf("Обратная:\n");
    printMatrix(inverse, n, n, m);

    if (!initMatrix(n, k, filename, a)) {
        cerr << "Error: cannot read matrix again for residual\n";
        return 1;
    }

    printf("Невязка: %.3e\n", residualNorm(a, inverse));
    printf("Время: %.6f s\n", seconds);
    return 0;
}
