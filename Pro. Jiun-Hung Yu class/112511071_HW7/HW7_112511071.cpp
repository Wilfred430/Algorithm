#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string File;
    ifstream in;
    cout << "Enter the filename: ";
    cin >> File;

    in.open(File);
    if (in.fail())
    {
        cerr << "Can't open the file !!!" << endl;
        return 0;
    }

    int pattern_num = 1;
    while (!in.eof())
    {
        vector<vector<int>> G(8, vector<int>(8, 0));
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                in >> G[i][j];
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << G[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    in.close();

    return 0;
}