#include <iostream>
#include <vector>
using namespace std;

vector<int> v; // 定義一個全域變數向量，用來存放輸入的數列

// 氣泡排序函數
void Bubble_sort()
{
    int tmp;
    for (int i = 0; i < v.size(); i++) // 外層迴圈控制執行的回合數
    {
        for (int j = 0; j < v.size() - 1; j++) // 內層迴圈進行元素的兩兩比較
        {
            if (v[j] > v[j + 1]) // 如果前一個元素大於後一個元素，則交換
            {
                tmp = v[j + 1]; // 使用暫存變數進行交換
                v[j + 1] = v[j];
                v[j] = tmp;
            }
        }
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
        for (int i = 0; i < num; i++) // 讀取數字並加入向量
        {
            cin >> tmp;
            v.push_back(tmp);
        }

        Bubble_sort(); // 對向量進行氣泡排序

        cout << "After sort : " << endl;
        for (auto it : v) // 輸出排序後的結果
        {
            cout << it << " ";
        }
        cout << endl; // 輸出換行符
    }

    return 0;
}
