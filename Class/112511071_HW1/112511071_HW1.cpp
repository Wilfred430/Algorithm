#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

void merge_combine(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1 + 1];
    int *R = new int[n2 + 1];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 || j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    delete[] L;
    delete[] R;
}

void merge_divide(vector<int> &arr, int left, int right)
{
    int mid = left + (right - left) / 2;
    if (left < right)
    {
        merge_divide(arr, left, mid);
        merge_divide(arr, mid + 1, right);
        merge_combine(arr, left, mid, right);
    }
}

void merge(vector<int> arr, int size)
{
    double end_time, start_time = clock();
    merge_divide(arr, 0, size - 1);
    end_time = clock();
    cout << fixed << setprecision(3) << "Merge Sort Time : " << (end_time - start_time) / (double)1000 << " seconds" << endl;
}

void insertion(vector<int> arr, int size)
{
    double end_time, start_time = clock();
    for(int i=1;i<size;i++)
    {
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    end_time = clock();
    cout << fixed << setprecision(3) << "Insertion Sort Time : " << (end_time - start_time) / (double)1000 << " seconds" << endl;
}

int main()
{
    srand(time(NULL));
    int size;
    while (cout << "Please enter the size of an array : ", cin >> size)
    {
        if (size == 0)
            break;
        vector<int> arr(size);
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand() % size;
        }
        merge(arr, size);
        insertion(arr, size);
        cout << "______________________________________________" << endl;
    }

    return 0;
}