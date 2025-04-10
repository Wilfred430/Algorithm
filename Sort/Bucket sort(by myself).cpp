#include <iostream>  // 引入标准输入输出流库
#include <vector>    // 引入向量容器的标头文件
#include <algorithm> // 引入算法库，提供标准算法功能如sort
#include <iterator>  // 引入迭代器标头文件
using namespace std;

void bucket_sort(vector<int> &v)
{
    // 确定输入数列的最大值和最小值
    int Max = *max_element(v.begin(), v.end());
    int Min = *min_element(v.begin(), v.end());

    // 计算每个桶的范围
    int Bucket = v.size() / 5;
    if (Bucket == 0)
        Bucket = 1; // 防止Bucket为0
    int gap = (Max - Min) / Bucket;
    if (gap == 0)
        gap = 1; // 防止gap为0

    vector<pair<int, int>> Pair; // 存储每个桶的范围

    // 将范围分割为多个桶
    for (int i = 0; i < Bucket - 1; i++)
    {
        Pair.push_back({Min + i * gap, Min + (i + 1) * gap - 1});
    }
    Pair.push_back({Min + (Bucket - 1) * gap, Max});

    vector<vector<int>> Count(Bucket); // 创建Bucket个桶（每个桶是一个向量）

    // 将元素分配到桶中
    for (auto it : v)
    {
        for (int i = 0; i < Bucket; i++)
        {
            if (Pair[i].first <= it && it <= Pair[i].second)
            {
                Count[i].push_back(it);
                break;
            }
        }
    }

    // 对每个桶中的元素进行排序
    for (int i = 0; i < Count.size(); i++)
    {
        sort(Count[i].begin(), Count[i].end());
    }

    // 将排序后的元素合并回原向量
    int tmp = 0;
    for (int i = 0; i < Count.size(); i++)
    {
        for (int j = 0; j < Count[i].size(); j++)
        {
            v[tmp] = Count[i][j];
            tmp++;
        }
    }
}

int main()
{
    int num;           // 保存输入的数字数量
    while (cin >> num) // 持续读取数字数量
    {
        vector<int> v(num); // 创建一个大小为num的向量v
        for (int i = 0; i < num; i++)
        {
            cin >> v[i]; // 读取每个数字并存入向量v
        }

        bucket_sort(v); // 调用桶排序函数对向量v进行排序

        cout << "After sort : " << endl;
        for (auto it : v) // 输出排序后的结果
        {
            cout << it << " ";
        }
        cout << endl; // 换行
    }

    return 0; // 程序正常结束
}
