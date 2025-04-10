#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> v; // 定義一個全域變數向量，用來存放輸入的數列

// 遞迴插值搜尋函數
bool recursive_interpolation_search(int left, int right, int target)
{
    while (left <= right && v[left] != v[right]) // 當左指標小於等於右指標且左、右元素不相等時
    {
        // 估計位置
        int index = left + ((right - left) / (v[right] - v[left])) * (target - v[left]);

        // 確保估計的索引在有效範圍內
        if (index < left || index > right)
        {
            break; // 如果估計索引超出範圍，退出循環
        }

        if (v[index] == target) // 如果找到目標
        {
            cout << "The position is: " << index + 1 << endl; // 顯示位置 (1-based index)
            return true;
        }
        else if (v[index] > target) // 如果估計的值大於目標
        {
            return recursive_interpolation_search(left, index - 1, target); // 遞迴搜尋左半部分
        }
        else if (v[index] < target) // 如果估計的值小於目標
        {
            return recursive_interpolation_search(index + 1, right, target); // 遞迴搜尋右半部分
        }
    }

    return false; // 如果未找到，返回 false
}

// 合併排序中的合併函數
void Merge(int left, int right, int mid)
{
    int n1 = mid - left + 1; // 計算左半部分的長度
    int n2 = right - mid;    // 計算右半部分的長度

    int *L = new int[n1 + 1]; // 動態分配陣列儲存左半部分
    int *R = new int[n2 + 1]; // 動態分配陣列儲存右半部分

    for (int i = 0; i < n1; i++)
    {
        L[i] = v[left + i]; // 複製左半部分到陣列 L
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = v[mid + i + 1]; // 複製右半部分到陣列 R
    }

    L[n1] = INT_MAX; // 設定左半部分的哨兵值
    R[n2] = INT_MAX; // 設定右半部分的哨兵值

    int i = 0, j = 0;
    for (int k = left; k <= right; k++) // 合併 L 和 R 到原向量 v 中
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

    delete[] L; // 釋放 L 陣列的記憶體
    delete[] R; // 釋放 R 陣列的記憶體
}

// 合併排序函數
void Merge_sort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2; // 計算中間點，避免溢位
        Merge_sort(left, mid);               // 遞迴排序左半部分
        Merge_sort(mid + 1, right);          // 遞迴排序右半部分
        Merge(left, right, mid);             // 合併已排序的兩部分
    }
}

int main()
{
    ios::sync_with_stdio(false); // 提升 IO 效能，解除 C++ 與 C 的 IO 綁定

    int num;

    while (cin >> num) // 持續讀取輸入的數字數量
    {
        if (num == 0)
        {
            break; // 如果輸入為0則退出程式
        }
        v.clear(); // 清空向量
        int tmp;
        for (int i = 0; i < num; i++)
        {
            cin >> tmp;       // 讀取數字
            v.push_back(tmp); // 將數字加入向量
        }

        Merge_sort(0, num - 1); // 使用合併排序進行排序

        cout << "Please enter a number which you want to search: ";
        cin >> tmp; // 讀取要搜尋的目標數字

        // 使用遞迴插值搜尋目標數字
        if (!recursive_interpolation_search(0, num - 1, tmp))
        {
            cout << "Not find between the array." << endl; // 如果未找到目標數字，輸出提示信息
        }
    }

    return 0;
}
