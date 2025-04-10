#include <iostream>
#include <deque>
#include <vector>
#include <string>
using namespace std;

// LSD 基數排序函數
void Radix_sort(vector<string> &v, int Max)
{
    // 從最低有效位開始排序
    for (int level = Max - 1; level >= 0; level--)
    {
        deque<deque<string>> q(10); // 創建10個雙端佇列，對應數字0-9
        for (int i = 0; i < v.size(); i++)
        {
            // 如果字串還有第 level 位字符，將它加入相應的佇列
            if (v[i].length() > level)
                q[int(v[i][level]) - int('0')].push_back(v[i]);
            else
                q[0].push_back(v[i]); // 如果字串長度不足，將其加入0號佇列
        }

        int index = 0;
        for (int i = 0; i < 10; i++)
        {
            while (!q[i].empty())
            {
                v[index] = q[i].front(); // 將佇列中的字串放回原向量
                q[i].pop_front();
                index++;
            }
        }
    }
}

int main()
{
    int num;
    while (cin >> num)
    {
        vector<string> v(num); // 創建一個大小為num的向量v
        for (int i = 0; i < num; i++)
        {
            cin >> v[i]; // 讀取每個字串並存入向量v
        }

        int Max = 0;
        for (auto it : v)
        {
            if (it.length() > Max)
            {
                Max = it.length(); // 獲取字串的最大長度
            }
        }

        Radix_sort(v, Max); // 執行LSD基數排序

        cout << "After sort: ";
        for (auto it : v)
        {
            cout << it << " "; // 輸出排序後的結果
        }
        cout << endl; // 換行
    }

    return 0; // 程式正常結束
}
