#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<double>> a(n, vector<double>(2 * n));

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }

        for (int j = 0; j < n; j++) {
            a[i][j+n] = (i==j);
        }

    }

    for (int c = 0; c < n; c++) {

        int mainRow = c;

        for (int r = c+1; r < n; r++) {
            if (abs(a[r][c]) > abs(a[mainRow][c])) {
                mainRow = r;
            }
        }

        if (abs(a[mainRow][c]) < 1e-12) {
            cout << "вырождена";
            return 0;
        }

        swap(a[c], a[mainRow]);

        double mainEl = a[c][c];

        for (int j = 0; j < 2*n; j++) {
            a[c][j] /= mainEl;
        }

        for (int r = 0; r < n; r++) {
            if (r == c) {
                continue;
            }

            double factor = a[r][c];

            for (int j = 0; j < 2 * n; j++) {
                a[r][j] -= factor * a[c][j];
            }
        }
    }

    cout << fixed << setprecision(6);

    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            cout << a[i][j];
            if (j + 1 < 2 * n) {
                cout << ' ';
            }
        }

        cout << '\n';
    }

    return 0;
}