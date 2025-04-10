#include <iostream>  // 引入標準輸出輸入流庫
#include <vector>    // 引入向量容器的標頭檔
#include <algorithm> // 引入算法庫，提供標準算法功能如swap
using namespace std; // 使用標準命名空間

int location(vector<int> &v, int left, int right)
{
    int pivot = v[right]; // 將最右邊的元素作為樞軸
    int i = left;         // 初始化i為left，用來追蹤大於pivot的元素
    int j = right - 1;    // 初始化j為right-1，用來追蹤小於pivot的元素

    while (i <= j)
    {
        while (i <= j && v[i] <= pivot)
            i++; // 從左向右移動i，直到找到大於樞軸的元素
        while (i <= j && v[j] >= pivot)
            j--; // 從右向左移動j，直到找到小於樞軸的元素

        if (i < j) // 如果i和j尚未交錯
        {
            swap(v[i], v[j]); // 交換v[i]和v[j]的元素
            i++;              // i向右移動一位
            j--;              // j向左移動一位
        }
    }

    swap(v[i], v[right]); // 將樞軸與v[i]交換，使樞軸位於正確位置
    return i;             // 返回樞軸的最終位置
}

void quick_sort(vector<int> &v, int left, int right)
{
    if (left < right)
    {
        int pos = location(v, left, right); // 獲取樞軸的正確位置
        quick_sort(v, left, pos - 1);       // 遞迴排序樞軸左邊的子數列
        quick_sort(v, pos + 1, right);      // 遞迴排序樞軸右邊的子數列
    }
}

int main()
{
    int num;           // 儲存用戶輸入的數字數量
    while (cin >> num) // 不斷從標準輸入讀取數字數量
    {
        vector<int> v(num); // 建立一個大小為num的向量v
        for (int i = 0; i < num; i++)
        {
            cin >> v[i]; // 讀取每個數字並存入向量v
        }

        quick_sort(v, 0, num - 1); // 呼叫quick_sort函數對向量v進行排序

        cout << "After sort : " << endl; // 輸出排序後的結果
        for (auto it : v)
        {
            cout << it << " "; // 輸出向量中的每個元素
        }
        cout << endl; // 換行
    }

    return 0; // 程式正常結束
}
