#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> v; // 定義一個全域變數向量，用來存放輸入的數列

// 選擇排序函數
void selection_sort()
{
    int min_index, tmp;
    for (int i = 0; i < v.size(); i++) // 外層迴圈：遍歷數列的每一個位置
    {
        min_index = i; // 假設當前索引 i 的元素是最小的
        for (int j = i + 1; j < v.size(); j++) // 內層迴圈：尋找剩餘部分中的最小元素
        {
            if (v[j] < v[min_index])
            {
                min_index = j; // 更新最小元素的索引
            }
        }
        // 將找到的最小元素與當前未排序部分的第一個元素交換
        if (min_index != i)
        {
            tmp = v[min_index]; // 使用暫存變數進行交換
            v[min_index] = v[i];
            v[i] = tmp;
        }
    }
}

int main()
{
    int num;
    while (cin >> num)
    {
        if (num == 0)
        {
            break; // 如果輸入為0則退出程式
        }
        v.clear(); // 清空向量以準備新的輸入
        int tmp;
        for (int i = 0; i < num; i++)
        {
            cin >> tmp;
            v.push_back(tmp); // 將輸入的數字加入向量
        }

        selection_sort(); // 對向量進行選擇排序

        cout << "After sort: ";

        for (auto it : v)
        {
            cout << it << " "; // 輸出排序後的結果
        }
        cout << endl; // 在輸出排序結果後換行
    }

    return 0;
}
