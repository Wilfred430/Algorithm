#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

vector<int> v; // 全域變數，用來存放要處理的數列

// 合併排序中的合併函數
void Merge(int left, int right, int mid)
{
    int n1 = mid - left + 1; // 左半部分的長度
    int n2 = right - mid;    // 右半部分的長度

    int *L = new int[n1 + 1]; // 暫存左半部分
    int *R = new int[n2 + 1]; // 暫存右半部分

    // 複製數據到左、右半部分
    for (int i = 0; i < n1; i++)
    {
        L[i] = v[left + i];
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = v[mid + 1 + i];
    }

    // 設定哨兵值
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = left; k <= right; k++) // 合併左右半部分
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

    delete[] L; // 釋放記憶體
    delete[] R;
}

// 合併排序
void Merge_sort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        Merge_sort(left, mid);      // 遞迴排序左半部分
        Merge_sort(mid + 1, right); // 遞迴排序右半部分
        Merge(left, right, mid);    // 合併已排序的兩部分
    }
}

// 遞迴二分搜尋
bool recursive_binary_sort(int left, int right, int target)
{
    if (left <= right) // 確保範圍內有元素
    {
        int mid = left + (right - left) / 2;
        if (v[mid] == target)
        {
            cout << "Found at position: " << mid + 1 << endl; // 顯示找到的元素位置
            return true;
        }
        else if (v[mid] < target)
        {
            return recursive_binary_sort(mid + 1, right, target); // 搜尋右半部分
        }
        else
        {
            return recursive_binary_sort(left, mid - 1, target); // 搜尋左半部分
        }
    }
    return false;
}

// 指數搜尋
void exponential_search(int target)
{
    int bound = 1;
    // 指數搜尋來找搜尋範圍
    while (bound < v.size() && v[bound] < target)
    {
        bound *= 2;
    }
    // 在範圍內進行二分搜尋
    if (!recursive_binary_sort(bound / 2, min(bound, (int)v.size() - 1), target))
    {
        cout << "Not find between the array." << endl;
    }
}

int main()
{
    int num;
    while (cin >> num)
    {
        if (num == 0)
        {
            break; // 如果輸入為0則退出
        }
        v.clear();
        int tmp;
        for (int i = 0; i < num; i++)
        {
            cin >> tmp;
            v.push_back(tmp);
        }

        Merge_sort(0, num - 1); // 對輸入的數列進行合併排序

        cout << "Please enter a number which you want to search: ";
        cin >> tmp; // 讀取要查找的數字

        exponential_search(tmp);
    }

    return 0;
}
