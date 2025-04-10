#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Shell 排序函數
void shell_sort(vector<int> &v)
{
    int gap = int(v.size()) / 2; // 初始間隔設置為數列長度的一半
    while (gap >= 1)             // 當間隔大於或等於1時進行排序
    {
        for (int i = 0; i + gap < v.size(); i++) // 遍歷數列，進行間隔為 gap 的插入排序
        {
            for (int j = i; j + gap < v.size(); j += gap) // 從當前元素起，每次移動 gap 單位
            {
                if (v[j + gap] < v[j]) // 如果間隔為 gap 的元素小於當前元素，則交換
                {
                    swap(v[j + gap], v[j]); // 使用 STL 的 swap 函數進行交換
                }
            }
        }
        gap /= 2; // 每次排序後將間隔縮小一半
    }
}

int main()
{
    int num;
    while (cin >> num) // 持續讀取輸入的數字數量
    {
        if (num == 0)
        {
            break; // 如果輸入為0則退出程式
        }
        int tmp;
        vector<int> v;
        for (int i = 0; i < num; i++) // 讀取數字並加入向量
        {
            cin >> tmp;
            v.push_back(tmp);
        }

        shell_sort(v); // 對向量進行 Shell 排序

        cout << "Sorted array : "; // 輸出排序後的數列

        for (auto it : v)
        {
            cout << it << " ";
        }

        cout << endl; // 輸出換行符
    }

    return 0;
}
