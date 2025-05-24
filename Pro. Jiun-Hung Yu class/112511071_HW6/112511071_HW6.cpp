#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

vector<double> Exhaustive(vector<double> &v1, vector<double> &v2, vector<double> &v3)
{
    vector<double> result;
    for(int i=0;i<v1.size();i++)
    {
        if(find(v2.begin(),v2.end(),v1[i]) != v2.end() && find(v3.begin(),v3.end(),v1[i]) != v3.end())
        {
            result.push_back(v1[i]);
        }
    }

    sort(result.begin(),result.end());

    return result;
}

// vector<double> LongestLCS(vector<double> &v1, vector<double> &v2, vector<double> &v3)
// {
// }

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

    vector<double> result_Ex = Exhaustive(v1, v2, v3);
    // vector<double> result_TA = LongestLCS(v1, v2, v3);

    cout << "Longest Common Subsequence by exhausive: ";
    for (auto it : result_Ex)
    {
        cout << it << " ";
    }
    cout << endl;

    cout << "Length of LCS by Ex: " << result_Ex.size() << endl;

    // cout << "Longest Common Subsequence by teacher: ";
    // for (auto it : result_TA)
    // {
    //     cout << it << " ";
    // }
    // cout << endl;

    // cout << "Length of LCS by TA: " << result_TA.size() << endl;

    return 0;
}
