#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <sstream>
#include <cmath>
using namespace std;

// Epsilon for floating-point comparison
const double EPSILON = 1e-9;

bool areEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

int LCS_Exhaustive(const vector<double> &X, const vector<double> &Y, const vector<double> &Z, int i, int j, int k) {
    if (i == 0 || j == 0 || k == 0)
        return 0;
    if (areEqual(X[i - 1], Y[j - 1]) && areEqual(X[i - 1], Z[k - 1]))
        return 1 + LCS_Exhaustive(X, Y, Z, i - 1, j - 1, k - 1);
    else
        return max(
            LCS_Exhaustive(X, Y, Z, i - 1, j, k),
            max(
                LCS_Exhaustive(X, Y, Z, i, j - 1, k),
                LCS_Exhaustive(X, Y, Z, i, j, k - 1)
            )
        );
}

void LCS_Exhaustive_Print(const vector<double> &X, const vector<double> &Y, const vector<double> &Z,
                          int i, int j, int k, vector<double> &lcs, vector<double> &best) {
    if (i == 0 || j == 0 || k == 0) {
        if (lcs.size() > best.size())
            best = lcs;
        return;
    }
    if (areEqual(X[i - 1], Y[j - 1]) && areEqual(X[i - 1], Z[k - 1])) {
        lcs.push_back(X[i - 1]);
        LCS_Exhaustive_Print(X, Y, Z, i - 1, j - 1, k - 1, lcs, best);
        lcs.pop_back();
    } else {
        LCS_Exhaustive_Print(X, Y, Z, i - 1, j, k, lcs, best);
        LCS_Exhaustive_Print(X, Y, Z, i, j - 1, k, lcs, best);
        LCS_Exhaustive_Print(X, Y, Z, i, j, k - 1, lcs, best);
    }
}

void LongestLCS(const vector<double> &v1, const vector<double> &v2, const vector<double> &v3,
                vector<vector<vector<int>>> &C, vector<vector<vector<tuple<int, int, int>>>> &b) {
    int n = v1.size();
    int m = v2.size();
    int f = v3.size();

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= f; k++) {
                C[i][j][k] = 0;
                b[i][j][k] = {0, 0, 0}; // Initialize boundary cases
            }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int z = 1; z <= f; z++) {
                if (areEqual(v1[i - 1], v2[j - 1]) && areEqual(v3[z - 1], v1[i - 1])) {
                    C[i][j][z] = C[i - 1][j - 1][z - 1] + 1;
                    b[i][j][z] = {-1, -1, -1};
                } else if (C[i - 1][j][z] >= C[i][j - 1][z] && C[i - 1][j][z] >= C[i][j][z - 1]) {
                    C[i][j][z] = C[i - 1][j][z];
                    b[i][j][z] = {-1, 0, 0};
                } else if (C[i][j - 1][z] >= C[i - 1][j][z] && C[i][j - 1][z] >= C[i][j][z - 1]) {
                    C[i][j][z] = C[i][j - 1][z];
                    b[i][j][z] = {0, -1, 0};
                } else {
                    C[i][j][z] = C[i][j][z - 1];
                    b[i][j][z] = {0, 0, -1};
                }
            }
        }
    }
}

void Print_LCS(const vector<vector<vector<tuple<int, int, int>>>> &b, const vector<double> &v, int i, int j, int z) {
    if (i == 0 || j == 0 || z == 0)
        return;
    if (b[i][j][z] == make_tuple(-1, -1, -1)) {
        Print_LCS(b, v, i - 1, j - 1, z - 1);
        cout << fixed << setprecision(6) << v[i - 1] << " ";
    } else if (b[i][j][z] == make_tuple(-1, 0, 0)) {
        Print_LCS(b, v, i - 1, j, z);
    } else if (b[i][j][z] == make_tuple(0, -1, 0)) {
        Print_LCS(b, v, i, j - 1, z);
    } else {
        Print_LCS(b, v, i, j, z - 1);
    }
}

int main() {
    srand((unsigned)time(NULL));

    // Check performance counter availability
    LARGE_INTEGER nFreq;
    if (!QueryPerformanceFrequency(&nFreq)) {
        cerr << "High-performance counter not supported!" << endl;
        return 1;
    }

    while (true) {
        cout << "Enter the size (0 to exit, max 100): ";
        int Size;
        cin >> Size;

        // Input validation
        if (Size == 0)
            break;
        if (Size < 0 || Size > 100) {
            cout << "Invalid size. Must be between 1 and 100." << endl;
            continue;
        }

        vector<double> v1, v2, v3;
        auto rand_double = []() {
            int denom = (rand() % 19) + 1; // 1~19
            return (rand() % 1000) / static_cast<double>(denom);
        };

        for (int i = 0; i < Size; i++) {
            v1.push_back(rand_double());
            v2.push_back(rand_double());
            v3.push_back(rand_double());
        }

        // Exhaustive timing
        LARGE_INTEGER nBeginTime, nEndTime;
        QueryPerformanceCounter(&nBeginTime);

        vector<double> lcs, best;
        LCS_Exhaustive_Print(v1, v2, v3, v1.size(), v2.size(), v3.size(), lcs, best);

        QueryPerformanceCounter(&nEndTime);
        double time_ex = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

        cout << "Exhaustive LCS length: " << best.size() << endl;
        cout << "Exhaustive LCS: ";
        for (double val : best)
            cout << fixed << setprecision(6) << val << " ";
        cout << endl;
        cout << "Exhaustive time: " << time_ex << " sec" << endl;

        // DP timing
        vector<vector<vector<int>>> C(v1.size() + 1, vector<vector<int>>(v2.size() + 1, vector<int>(v3.size() + 1)));
        vector<vector<vector<tuple<int, int, int>>>> b(v1.size() + 1, vector<vector<tuple<int, int, int>>>(v2.size() + 1, vector<tuple<int, int, int>>(v3.size() + 1)));

        QueryPerformanceCounter(&nBeginTime);

        LongestLCS(v1, v2, v3, C, b);

        QueryPerformanceCounter(&nEndTime);
        double time_dp = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

        cout << "DP LCS length: " << C[v1.size()][v2.size()][v3.size()] << endl;
        cout << "DP LCS: ";
        Print_LCS(b, v1, v1.size(), v2.size(), v3.size());
        cout << endl;
        cout << "DP time: " << time_dp << " sec" << endl;
    }

    return 0;
}