#include <iostream>  // 引入標準輸入輸出流
#include <vector>    // 引入向量容器
#include <map>       // 引入映射容器
using namespace std; // 使用標準命名空間

void counting_sort(vector<int> &v) // 定義計數排序函數，接受一個整數向量的引用
{
    map<int, int> m; // 定義一個映射，用於儲存每個數字的出現次數

    // 統計每個元素出現的次數
    for (int i = 0; i < v.size(); i++) // 遍歷向量中的每個元素
    {
        m[v[i]]++; // 增加該數字的計數，若該數字不存在則自動初始化為1
    }

    // 累積前綴和
    int sum = 0;         // 定義一個變量儲存累積和
    for (auto &pair : m) // 遍歷映射中的每個元素
    {
        sum += pair.second; // 累加每個元素的出現次數
        pair.second = sum;  // 更新該元素的值為累積和
    }

    vector<int> sorted(v.size()); // 定義一個新向量來儲存排序結果

    // 從原向量中獲取元素並放置到新向量中
    for (int i = v.size() - 1; i >= 0; i--) // 逆向遍歷原向量中的每個元素
    {
        sorted[m[v[i]] - 1] = v[i]; // 根據映射中的位置將元素放置到新向量中
        m[v[i]]--;                  // 減少該元素的計數以便處理重複的數字
    }

    // 將排序結果賦值回原向量
    v = sorted; // 將排序好的新向量賦值給原向量
}

int main() // 主函數
{
    int num;           // 定義一個整數變量來儲存數字的個數
    while (cin >> num) // 當從輸入中獲取到有效的數字個數時
    {
        vector<int> v(num);           // 定義一個向量，大小為輸入的數字個數
        for (int i = 0; i < num; i++) // 遍歷每個輸入的數字
        {
            cin >> v[i]; // 將輸入的數字存入向量中
        }

        counting_sort(v); // 調用計數排序函數對向量進行排序

        cout << "After sort : " << endl; // 輸出排序後的結果提示
        for (auto it : v)                // 遍歷排序後的向量
        {
            cout << it << " "; // 輸出每個元素
        }

        cout << endl; // 輸出換行符
    }

    return 0; // 返回0，表示程序成功結束
}
