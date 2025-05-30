#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

vector<int> Counting_sort(const vector<int> &v)
{
    int Max = INT_MIN;
    for (auto it : v)
    {
        Max = max(it, Max);
    }

    vector<int> C(Max + 1, 0);

    for (int i = 0; i < v.size(); i++)
    {
        C[v[i]]++;
    }

    for(int i=1;i<=Max;i++)
    {
        C[i] += C[i-1];
    }

    vector<int> result(v.size());

    for(int i=v.size()-1;i>=0;i--)
    {
        result[C[v[i]]-1] = v[i]; //小心超出邊界
        C[v[i]]--;
    }

    return result;
}

int main()
{
    int Size;
    while (cout << "Please enter the size of the array: ", cin >> Size)
    {
        vector<int> v(Size, 0);
        cout << "Please enter the entry of the array(seperate by space): ";
        for (int i = 0; i < v.size(); i++)
        {
            cin >> v[i];
        }

        vector<int> result = Counting_sort(v);

        cout << "After sorted: ";
        for (auto it : result)
        {
            cout << it << " ";
        }
        cout << endl;
    }

    return 0;
}