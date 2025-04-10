#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void selection_max_sort(vector<int> &v)
{
    // 从向量的末端向前遍历进行选择排序
    for (auto it = v.rbegin(); it != prev(v.rend()); it++)
    {
        auto adre = it; // 需要使用auto来推导迭代器类型
        int Max = *it;  // 当前迭代器指向的最大值
        for (auto is = next(it); is != v.rend(); is++)
        {
            if (*is > Max)
            {
                Max = *is; // 更新最大值
                adre = is; // 更新最大值的迭代器位置
            }
        }
        // 交换最大值和当前位置的值
        if (adre != it) // 如果最大值位置发生了变化，则交换
            iter_swap(adre, it);
    }
}

int main()
{
    int num;
    while (cin >> num)
    {
        vector<int> v(num);
        for (size_t i = 0; i < num; i++)
        {
            cin >> v[i];
        }

        selection_max_sort(v); // 调用选择排序

        cout << "After sort : ";
        for (auto it : v)
        {
            cout << it << " ";
        }
        cout << endl;
    }

    return 0;
}
