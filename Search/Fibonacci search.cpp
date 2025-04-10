#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> v; // 定義一個全域變數向量，用來存放輸入的數列

// 用於生成費氏數列直到特定大小
vector<int> generateFibonacci(int size)
{
    vector<int> fib = {0, 1};  // 初始化費氏數列前兩個元素
    while (fib.back() <= size) // 當最後一個元素小於等於指定大小時繼續生成
    {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]); // 新增下一個費氏數
    }
    return fib; // 返回生成的費氏數列....
}

// 費氏搜尋函數
bool Fibonacci_search(int target)
{
    int size = v.size();
    vector<int> fib = generateFibonacci(size); // 生成費氏數列

    int fibM = fib.size() - 1; // 指向費氏數列中的最大數
    int offset = -1;           // 初始化偏移量

    while (fib[fibM] > 1) // 當費氏數大於1時繼續搜尋
    {
        int i = min(offset + fib[fibM - 2], size - 1); // 計算要比較的位置

        if (v[i] < target) // 如果該位置的元素小於目標
        {
            fibM = fibM - 1; // 縮小範圍至右側
            offset = i;      // 更新偏移量
        }
        else if (v[i] > target) // 如果該位置的元素大於目標
        {
            fibM = fibM - 2; // 縮小範圍至左側
        }
        else
        {
            cout << "The position is " << i + 1 << endl; // 找到目標，顯示其位置（1-based index）
            return true;                                 // 返回 true 表示找到目標
        }
    }

    // 特殊情況：檢查最後一個位置
    if (fib[fibM - 1] && v[offset + 1] == target)
    {
        cout << "The position is " << offset + 2 << endl;
        return true;
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

        // 使用費氏搜尋目標數字
        if (!Fibonacci_search(tmp))
        {
            cout << "Not found in the array." << endl; // 如果未找到目標數字，輸出提示信息
        }
    }

    return 0;
}
