#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> v;

// 插值搜尋函數
bool iterative_interpolation_search(int left, int right, int target)
{
    while (left <= right && v[left] != v[right])
    {
        // 估計位置
        int index = left + ((right - left) / (v[right] - v[left])) * (target - v[left]);

        // 確保索引在範圍內
        if (index < left || index > right)
        {
            break;
        }

        if (v[index] == target)
        {
            cout << "The position is: " << index + 1 << endl;
            return true;
        }
        else if (v[index] > target)
        {
            right = index - 1;
        }
        else if (v[index] < target)
        {
            left = index + 1;
        }
    }

    return false;
}

// 合併排序中的合併函數
void Merge(int left, int right, int mid)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1 + 1];
    int *R = new int[n2 + 1];

    for (int i = 0; i < n1; i++)
    {
        L[i] = v[left + i];
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = v[mid + i + 1];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = left; k <= right; k++)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
    }

    delete[] L;
    delete[] R;
}

// 合併排序函數
void Merge_sort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        Merge_sort(left, mid);
        Merge_sort(mid + 1, right);
        Merge(left, right, mid);
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int num;

    while (cin >> num)
    {
        if (num == 0)
        {
            break;
        }
        v.clear();
        int tmp;
        for (int i = 0; i < num; i++)
        {
            cin >> tmp;
            v.push_back(tmp);
        }

        Merge_sort(0, num - 1);

        cout << "Please enter a number which you want to search: ";
        cin >> tmp;

        if (!iterative_interpolation_search(0, num - 1, tmp))
        {
            cout << "Not find between the array." << endl;
        }
    }

    return 0;
}