#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 標定樞軸的位置函數
int pivot_location(vector<int> &v, int left, int right) {
    int pivot = v[right]; // 選擇最右邊的元素作為樞軸
    int i = left - 1; // 初始化較小元素的索引

    for (int j = left; j < right; j++) { // 遍歷數列，將小於樞軸的元素移動到左側
        if (v[j] < pivot) {
            i++; // 增加較小元素的索引
            swap(v[i], v[j]); // 將較小的元素與當前元素交換
        }
    }

    swap(v[i + 1], v[right]); // 將樞軸移動到正確的位置
    return i + 1; // 返回樞軸的位置
}

// 快速排序函數
void quick_sort(vector<int> &v, int left, int right) {
    if (left < right) { // 當左指標小於右指標時繼續排序
        int pos = pivot_location(v, left, right); // 標定樞軸位置
        quick_sort(v, left, pos - 1); // 遞迴排序樞軸左側部分
        quick_sort(v, pos + 1, right); // 遞迴排序樞軸右側部分
    }
}

int main() {
    int num;
    while(cin >> num) { // 持續讀取輸入的數字數量
        if(num == 0) {
            break; // 如果輸入為0則退出程式
        }
        vector<int> v(num); // 定義一個向量來存放數字
        for(int i = 0; i < num; i++) { // 讀取數字並加入向量
            cin >> v[i];
        }

        quick_sort(v, 0, num - 1); // 對向量進行快速排序

        cout << "Sorted array: "; // 輸出排序後的結果
        for(const auto &it : v) {
            cout << it << " ";
        }
        cout << endl; // 輸出換行符
    }

    return 0;
}
