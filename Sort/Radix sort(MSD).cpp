#include <iostream>
#include <vector>
#include <deque>
#include <string>
using namespace std;

// MSD 基數排序的遞迴函數
void MSD_radix_sort(vector<string> &v, int left, int right, int level)
{
    if (left >= right || level < 0) // 基礎條件：當只剩一個元素或層數小於0時停止
        return;

    vector<deque<string>> buckets(10); // 創建10個桶，用於放置數字0-9的字串

    // 將字串根據當前位數分配到相應的桶中
    for (int i = left; i <= right; i++)
    {
        if (v[i].length() <= level)     // 如果字串長度不足以到達當前層數
            buckets[0].push_back(v[i]); // 放入0號桶
        else
        {
            int digit = v[i][level] - '0';  // 取得當前位數的數字
            buckets[digit].push_back(v[i]); // 放入相應的桶
        }
    }

    // 將桶中的元素按順序放回原向量，並遞迴對每個桶進行排序
    int index = left;
    for (int i = 0; i < 10; i++)
    {
        for (auto &str : buckets[i])
        {
            v[index++] = str; // 將排序後的元素放回原向量
        }
        // 只對非空桶遞迴排序下一位
        if (!buckets[i].empty())
        {
            MSD_radix_sort(v, left, index - 1, level + 1); // 對該桶的字串進行下一層排序
            left = index;                                  // 更新左邊界
        }
    }
}

int main()
{
    int num;
    while (cin >> num)
    {
        vector<string> v(num);
        for (int i = 0; i < num; i++)
        {
            cin >> v[i];
        }

        // 開始進行MSD基數排序，從第0位開始
        MSD_radix_sort(v, 0, num - 1, 0);

        cout << "After sort: ";
        for (auto it : v)
        {
            cout << it << " "; // 輸出排序後的結果
        }
        cout << endl;
    }

    return 0;
}
