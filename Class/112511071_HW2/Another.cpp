#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<tuple>
#include<algorithm>
#include<climits>
using namespace std;

//vector<tuple<int,int,float>> Max_sum;

struct Subarray
{
    int low;
    int high;
    float sum;
};

Subarray Find_Maximum_Crossing_Subarray(vector<float>& v, int low, int mid, int high)
{
    Subarray Sub;
    float Left_sum = INT_MIN;
    float sum = 0;
    for(int i = mid; i >= low; i--)
    {
        sum += v[i];
        if(sum > Left_sum)
        {
            Left_sum = sum;
            Sub.low = i;
        }
    }
    float Right_sum = INT_MIN;
    sum = 0;
    for(int i = mid + 1; i <= high; i++)
    {
        sum += v[i];
        if(sum > Right_sum)
        {
            Right_sum = sum;
            Sub.high = i;
        }
    }

    Sub.sum = Right_sum + Left_sum;

    return Sub;
}

Subarray Find_Maximum_Subarray(vector<float>& v, int low, int high)
{
    Subarray Sub;
    if(low == high)
    {
        Sub.low = low;
        Sub.high = high;
        Sub.sum = v[low];

        return Sub;
    }

    int mid = low + (high - low) / 2;

    Subarray Left = Find_Maximum_Subarray(v, low, mid);
    Subarray Right = Find_Maximum_Subarray(v, mid + 1, high);
    Subarray Cross = Find_Maximum_Crossing_Subarray(v, low, mid, high);
    //cout<<Left.sum<<endl;
    if(Left.sum >= Right.sum && Left.sum >= Cross.sum)
    {
        return Left;
    }
    else if(Right.sum >= Left.sum && Right.sum >= Cross.sum)
    {
        return Right;
    }
    else
    {
        return Cross;
    }
}

int main()
{
    ifstream in;
    in.open("C:/Program Learning/Algorithm/Class/112511071_HW2/data.txt");
    if(in.fail())
    {
        cout << "Can't open the data. \n";
        exit(1);
    }

    vector<float> v;
    int lose;
    float need;
    while(in >> lose >> need)
    {
        v.push_back(need);
    }

    /*for(auto it : v)
    {
        cout << it << endl;
    }*/

    Subarray result;
    result = Find_Maximum_Subarray(v, 0, v.size() - 1);

    cout << "Start from " << result.low << " to " << result.high << endl;
    cout << "Maximum sum is " << result.sum << endl;

    in.close();

    return 0;
}