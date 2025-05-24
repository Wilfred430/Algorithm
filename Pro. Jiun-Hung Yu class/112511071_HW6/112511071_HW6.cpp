#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <string>
#include <tuple>
#include <sstream>
using namespace std;

int LCS_Exhaustive(const vector<double> &X, const vector<double> &Y, const vector<double> &Z, int i, int j, int k)
{
    if (i == 0 || j == 0 || k == 0)
        return 0;
    if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1])
        return 1 + LCS_Exhaustive(X, Y, Z, i - 1, j - 1, k - 1);
    else
        return max({LCS_Exhaustive(X, Y, Z, i - 1, j, k),
                    LCS_Exhaustive(X, Y, Z, i, j - 1, k),
                    LCS_Exhaustive(X, Y, Z, i, j, k - 1)});
}

void LCS_Exhaustive_Print(const vector<double> &X, const vector<double> &Y, const vector<double> &Z,
                          int i, int j, int k, vector<double> &lcs, vector<double> &best)
{
    if (i == 0 || j == 0 || k == 0)
    {
        if (lcs.size() > best.size())
            best = lcs;
        return;
    }
    if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1])
    {
        lcs.push_back(X[i - 1]);
        LCS_Exhaustive_Print(X, Y, Z, i - 1, j - 1, k - 1, lcs, best);
        lcs.pop_back();
    }
    else
    {
        LCS_Exhaustive_Print(X, Y, Z, i - 1, j, k, lcs, best);
        LCS_Exhaustive_Print(X, Y, Z, i, j - 1, k, lcs, best);
        LCS_Exhaustive_Print(X, Y, Z, i, j, k - 1, lcs, best);
    }
}

void LongestLCS(const vector<double> &v1, const vector<double> &v2, const vector<double> &v3, vector<vector<vector<int>>> &C, vector<vector<vector<tuple<int, int, int>>>> &b)
{
    int n = v1.size();
    int m = v2.size();
    int f = v3.size();

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= f; k++)
                C[i][j][k] = 0;

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            for (int z = 1; z < f + 1; z++)
            {
                if (v1[i - 1] == v2[j - 1] && v3[z - 1] == v1[i - 1])
                {
                    C[i][j][z] = C[i - 1][j - 1][z - 1] + 1;
                    b[i][j][z] = {-1, -1, -1};
                }
                else if (C[i - 1][j][z] >= C[i][j - 1][z] && C[i - 1][j][z] >= C[i][j][z - 1])
                {
                    C[i][j][z] = C[i - 1][j][z];
                    b[i][j][z] = {-1, 0, 0};
                }
                else if (C[i][j - 1][z] >= C[i - 1][j][z] && C[i][j - 1][z] >= C[i][j][z - 1])
                {
                    C[i][j][z] = C[i][j - 1][z];
                    b[i][j][z] = {0, -1, 0};
                }
                else
                {
                    C[i][j][z] = C[i][j][z - 1];
                    b[i][j][z] = {0, 0, -1};
                }
            }
        }
    }
}
void Print_LCS(const vector<vector<vector<tuple<int, int, int>>>> &b, const vector<double> &v, int i, int j, int z)
{
    if (i == 0 || j == 0 || z == 0)
        return;

    if (b[i][j][z] == make_tuple(-1, -1, -1))
    {
        Print_LCS(b, v, i - 1, j - 1, z - 1);
        cout << v[i - 1] << " ";
    }
    else if (b[i][j][z] == make_tuple(-1, 0, 0))
    {
        Print_LCS(b, v, i - 1, j, z);
    }
    else if (b[i][j][z] == make_tuple(0, -1, 0))
    {
        Print_LCS(b, v, i, j - 1, z);
    }
    else
    {
        Print_LCS(b, v, i, j, z - 1);
    }
}

int main()
{
    vector<double> v1;
    vector<double> v2;
    vector<double> v3;

    string tmp_1, tmp_2, tmp_3;
    double temp;

    cout << "Please enter sequences with elements seperated by spaces." << endl;
    cout << "Enter the elements of sequence X: ";
    getline(cin, tmp_1);
    stringstream ss_1(tmp_1);
    while (ss_1 >> temp)
    {
        v1.push_back(temp);
    }

    cout << "Enter the elements of sequence Y: ";
    getline(cin, tmp_2);
    stringstream ss_2(tmp_2);
    while (ss_2 >> temp)
    {
        v2.push_back(temp);
    }

    cout << "Enter the elements of sequence Z: ";
    getline(cin, tmp_3);
    stringstream ss_3(tmp_3);
    while (ss_3 >> temp)
    {
        v3.push_back(temp);
    }

    vector<double> lcs, best;
    LCS_Exhaustive_Print(v1, v2, v3, v1.size(), v2.size(), v3.size(), lcs, best);
    reverse(best.begin(), best.end());
    cout << "Longest Common Subsequence by EX: ";
    for (auto d : best)
        cout << d << " ";
    cout << endl;
    cout << "Length of LCS by EX: " << best.size() << endl;

    vector<vector<vector<int>>> C(v1.size() + 1, vector<vector<int>>(v2.size() + 1, vector<int>(v3.size() + 1)));
    vector<vector<vector<tuple<int, int, int>>>> b(v1.size() + 1, vector<vector<tuple<int, int, int>>>(v2.size() + 1, vector<tuple<int, int, int>>(v3.size() + 1)));

    LongestLCS(v1, v2, v3, C, b);

    cout << "Longest Common Subsequence by TA: ";

    Print_LCS(b, v1, v1.size(), v2.size(), v3.size());

    cout << "\nLength of LCS by TA: " << C[v1.size()][v2.size()][v3.size()] << endl;

    return 0;
}
