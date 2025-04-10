#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 桶排序函數
void bucket_sort(vector<int> &arr)
{
    int n = arr.size(); // 獲取向量的大小

    // 找到最大值和最小值以便確定每個桶的範圍
    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());

    // 如果所有元素都相等，直接返回
    if (max_val == min_val)
        return;

    // 創建 n 個空的桶，每個桶都是一個向量
    vector<vector<int>> buckets(n);

    // 將每個元素分配到相應的桶中
    for (int i = 0; i < n; i++)
    {
        // 計算桶索引，將元素範圍標準化到 [0, 1) 之間，再乘以桶的數量 n
        int bucket_index = (arr[i] - min_val) * (n - 1) / (max_val - min_val);
        buckets[bucket_index].push_back(arr[i]);
    }

    // 對每個桶中的元素進行排序
    for (int i = 0; i < n; i++)
    {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // 將所有桶中的元素連接起來，並回填到原陣列中
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            arr[index++] = buckets[i][j];
        }
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    while (cin >> n)
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        // 執行桶排序
        bucket_sort(arr);

        cout << "After sorting: ";
        for (auto num : arr)
        {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
