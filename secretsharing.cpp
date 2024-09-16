#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cctype>

using namespace std;

int baseToDecimal(string value, int base) {
    int result = 0;
    for (char digit : value) {
        if (isdigit(digit)) {
            result = result * base + (digit - '0');
        } else {
            result = result * base + (toupper(digit) - 'A' + 10);
        }
    }
    return result;
}

vector<double> gaussianElimination(vector<vector<double>>& matrix) {
    int n = matrix.size();

    for (int i = 0; i < n; ++i) {
        double diagElement = matrix[i][i];
        if (diagElement == 0) {
            cerr << "Error: Matrix is singular or nearly singular" << endl;
            exit(1);
        }
        for (int j = 0; j <= n; ++j) {
            matrix[i][j] /= diagElement;
        }

        for (int k = i + 1; k < n; ++k) {
            double factor = matrix[k][i];
            for (int j = 0; j <= n; ++j) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    vector<double> result(n);
    for (int i = n - 1; i >= 0; --i) {
        result[i] = matrix[i][n];
        for (int j = i + 1; j < n; ++j) {
            result[i] -= matrix[i][j] * result[j];
        }
    }

    return result;
}

int main() {
    int n, k;
    cout << "Enter number of points (n): ";
    cin >> n;
    cout << "Enter minimum number of points to solve (k): ";
    cin >> k;
    
    if (n < k) {
        cerr << "Error: Number of points must be at least equal to k" << endl;
        return 1;
    }

    vector<pair<int, int>> points;

    for (int i = 0; i < n; ++i) {
        int x, base;
        string valueStr;
        
        cout << "Enter x for point " << i + 1 << ": ";
        cin >> x;
        cout << "Enter base for y value (e.g., 10 for decimal, 16 for hexadecimal): ";
        cin >> base;
        cout << "Enter y value as a string: ";
        cin >> valueStr;

        int y = baseToDecimal(valueStr, base);
        points.push_back(make_pair(x, y));
    }

    vector<vector<double>> matrix(k, vector<double>(k + 1, 0));

    for (int i = 0; i < k; ++i) {
        int x = points[i].first;
        int y = points[i].second;

        for (int j = 0; j < k; ++j) {
            matrix[i][j] = pow(x, k - 1 - j);
        }
        matrix[i][k] = y;
    }

    vector<double> coefficients = gaussianElimination(matrix);

    cout << "The polynomial coefficients are:" << endl;
    for (int i = 0; i < coefficients.size(); ++i) {
        cout << "a_" << (k - 1 - i) << " = " << coefficients[i] << endl;
    }

    cout << "The constant term (c) is: " << coefficients[k - 1] << endl;

    return 0;
}
