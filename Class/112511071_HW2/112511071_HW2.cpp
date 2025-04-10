#include <iostream>
#include <fstream> // 使用 file I/O
#include <cstdlib> // 使用 exit
#include <vector>
#include <algorithm> // 使用 sort
#include <cmath>     // 使用 infinite

using namespace std;

// 定義一個結構體 Subarray，用來儲存子陣列的資訊
struct Subarray
{
    int low;   // 子陣列的起始索引
    int high;  // 子陣列的結束索引
    float sum; // 子陣列的總和
};

vector<Subarray> Min_size; // 用來儲存所有可能的子陣列

// 尋找跨越中點的最大子陣列
Subarray Find_Maximum_Crossing_Subarray(const vector<float> &v, int low, int mid, int high)
{
    Subarray Sub;
    float Left_sum = -INFINITY, Right_sum = -INFINITY, sum = 0;

    // 從中點向左尋找最大子陣列
    for (int i = mid; i >= low; i--)
    {
        sum += v[i];
        if (sum > Left_sum)
        {
            Left_sum = sum;
            Sub.low = i;
        }
    }

    sum = 0;
    // 從中點向右尋找最大子陣列
    for (int i = mid + 1; i <= high; i++)
    {
        sum += v[i];
        if (sum > Right_sum)
        {
            Right_sum = sum;
            Sub.high = i;
        }
    }

    Sub.sum = Right_sum + Left_sum; // 計算跨越中點的子陣列總和

    Min_size.push_back(Sub); // 將結果存入 Min_size 中

    return Sub;
}

// 尋找最大子陣列
Subarray Find_Maximum_Subarray(const vector<float> &v, int low, int high)
{
    if (low == high)
    {
        Min_size.push_back({low, high, v[low]}); // 如果只有一個元素，直接回傳
        return {low, high, v[low]};
    }

    int mid = low + (high - low) / 2;
    Subarray Left = Find_Maximum_Subarray(v, low, mid);                 // 遞迴尋找左半部分的最大子陣列
    Subarray Right = Find_Maximum_Subarray(v, mid + 1, high);           // 遞迴尋找右半部分的最大子陣列
    Subarray Cross = Find_Maximum_Crossing_Subarray(v, low, mid, high); // 尋找跨越中點的最大子陣列

    // 比較左半部分、右半部分和跨越中點的子陣列，回傳總和最大的子陣列
    if (Left.sum >= Right.sum && Left.sum >= Cross.sum) // 當最佳區間在 left
    {
        Min_size.push_back(Left); // 將 left 可能區間加入
        return Left;
    }
    else if (Right.sum >= Left.sum && Right.sum >= Cross.sum) // 當最佳區間在 right
    {
        Min_size.push_back(Right); // 將 right 可能區間加入
        return Right;
    }
    else // 當最佳區間在 cross
    {
        Min_size.push_back(Cross); // 將 cross 可能區間加入
        return Cross;
    }
}

// 比較函數，用於排序子陣列
bool Compare(const Subarray &a, const Subarray &b)
{
    if (a.sum != b.sum)
        return a.sum > b.sum; // 優先按總和從大到小排序
    else if ((a.high - a.low) != (b.high - b.low))
        return (a.high - a.low) < (b.high - b.low); // 總和相同時，按長度從小到大排序
    else
        return a.low < b.low; // 總和和長度都相同時，按起始索引升序排序
}

int main()
{
    // 讀取檔案
    ifstream in("data.txt"); // 請根據實際路徑調整
    if (!in)
    {
        cerr << "Can't open the file\n";
        return 1;
    }

    vector<float> v;
    int leak; // 前面序號，但不重要
    float need;
    while (in >> leak >> need)
        v.push_back(need); // 將檔案中的數據讀入 vector

    // 尋找最大子陣列
    Find_Maximum_Subarray(v, 0, v.size() - 1); // 觸發 recursion

    // 對子陣列進行排序
    sort(Min_size.begin(), Min_size.end(), Compare);

    // 移除重複的子陣列
    Min_size.erase(unique(Min_size.begin(), Min_size.end(), [](const Subarray &a, const Subarray &b)
                          { return a.high == b.high && a.low == b.low && a.sum == b.sum; }), // 刪除 high、low、sum 都相同的組合
                   Min_size.end());

    // 找出最大總和和最小間隔
    float max_sum = Min_size[0].sum;                  // 最大的區績總和
    int min_gap = Min_size[0].high - Min_size[0].low; // 最小的區間差

    // 輸出所有符合最大總和和最小間隔的子陣列
    for (const auto &sub : Min_size) // 用 auto 輸出
    {
        if (sub.sum == max_sum && (sub.high - sub.low) == min_gap) // 當區間最大值及集合大小相同時
        {
            cout << "Start from " << sub.low + 1 << " to " << sub.high + 1 << endl; // 輸出區間的左右邊界
        }
        else
        {
            break; // 一旦超出最大總和或最小間隔，停止輸出
        }
    }
    cout << "Maximum sum is " << max_sum << endl; // 輸出最大的區間和

    in.close();       // 關檔
    Min_size.clear(); // 清除全域變數的資料

    return 0;
}