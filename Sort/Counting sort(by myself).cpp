#include <iostream>  // 引入標準輸入輸出流
#include <algorithm> // 引入標準算法庫
#include <vector>    // 引入向量容器
#include <map>       // 引入映射容器
#include <iterator>  // 引入迭代器支持
using namespace std; // 使用標準命名空間

void counting_sort(vector<int> &v) // 定義計數排序函數，接受一個整數向量的引用
{
    map<int, int> m;                   // 定義一個映射，用於儲存每個數字的出現次數
    for (int i = 0; i < v.size(); i++) // 遍歷向量中的每個元素
    {
        if (m.find(v[i]) != m.end()) // 如果數字已經在映射中
        {
            m[v[i]]++; // 增加該數字的計數
        }
        else // 如果數字不在映射中
        {
            m.insert(pair<int, int>(v[i], 1)); // 將該數字插入映射並設計數為1
        }
    }

    for (auto it = next(m.begin()); it != m.end(); it++) // 從映射的第二個元素開始，遍歷每個元素
    {
        it->second += prev(it)->second; // 將前一個元素的計數加到當前元素上
    }

    for (auto it = m.rbegin(); it != m.rend(); it++) // 逆向遍歷映射中的每個元素
    {
        while (it->second > next(it)->second) // 當前元素的計數大於下一個元素的計數時
        {
            v[it->second - 1] = it->first; // 將數字放到結果向量的相應位置
            it->second--;                  // 減少當前元素的計數
        }
    }
}

int main() // 主函數
{
    int num;           // 定義一個整數變量，用於儲存數字的個數
    while (cin >> num) // 當輸入的數字個數有效時
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
        v.clear();    // 清空向量
    }

    return 0; // 返回0，表示程序成功結束
}
