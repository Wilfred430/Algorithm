#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> v; // 用來存儲輸入的數字

void Merge(int left, int right, int mid)
{
    int n1 = mid - left + 1; // 左半部分長度
    int n2 = right - mid;    // 右半部分長度

    int *L = new int[n1 + 1]; // 左半部分的臨時陣列
    int *R = new int[n2 + 1]; // 右半部分的臨時陣列

    // 將數據分別拷貝到左半部分和右半部分
    for (int i = 0; i < n1; i++)
    {
        L[i] = v[left + i];
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = v[mid + 1 + i];
    }

    // 在L和R的末尾添加最大整數值，方便合併
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = left; k <= right; k++) // 修改這裡，從left開始
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

    delete[] L; // 釋放動態分配的記憶體
    delete[] R;
}

void Merge_sort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2; // 計算中間索引
        Merge_sort(left, mid);               // 遞迴排序左半部分
        Merge_sort(mid + 1, right);          // 遞迴排序右半部分
        Merge(left, right, mid);             // 合併已排序的兩部分
    }
}

bool iterator_binary_search(int target)
{
    int left = 0, right = v.size() - 1;
    while (left <= right) // 修改這裡為 <=
    {
        int mid = left + (right - left) / 2;
        if (v[mid] == target)
        {
            cout << mid + 1 << endl; // 輸出1-based索引
            return true;
        }
        else if (v[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return false; // 如果找不到則返回false
}

int main()
{
    int num;
    while (cin >> num)
    {
        int tmp;
        v.clear(); // 清空vector
        for (int i = 0; i < num; i++)
        {
            cin >> tmp;
            v.push_back(tmp);
        }

        Merge_sort(0, num - 1); // 對數據進行合併排序

        // 這裡要求使用者輸入想要搜尋的數字
        cout << "Enter number to search: ";
        cin >> tmp;

        if (!iterator_binary_search(tmp))
        {
            cout << "Not find between the array." << endl;
        }
    }

    return 0;
}
