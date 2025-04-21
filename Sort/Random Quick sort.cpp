#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

int Partition(vector<int>& v,int left,int right)
{
    int tmp = v[right];
    int i=left-1;
    for(int j=left;j<=right-1;j++)
    {
        if(v[j]<=tmp)
        {
            i++;
            swap(v[j],v[i]);
        }
    }
    swap(v[i+1],v[right]);

    return i+1;
}

int Randomized_Partition(vector<int>& v,int left,int right)
{
    int i=left+rand()%(right-left+1);
    swap(v[right],v[i]);
    return Partition(v,left,right);
}

void RM_Quicksort(vector<int>& v,int left,int right)
{
    if(left < right)
    {
        int pivot = Randomized_Partition(v,left,right);
        RM_Quicksort(v,left,pivot-1);
        RM_Quicksort(v,pivot+1,right);
    }
}

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    int num;
    while(1)
    {
        cout << "Please enter the size of the array: ";
        cin >> num;
        if(num == 0) break;
        vector<int> v(num);
        cout << "Please enter the entry the array have: ";
        for (int i = 0; i < num; i++)
        {
            cin >> v[i];
        }

        RM_Quicksort(v,0,num-1);

        cout << "After sorted: ";
        for(auto it:v)
        {
            cout << it << " ";
        }
        cout << endl;
    }

    return 0;
}