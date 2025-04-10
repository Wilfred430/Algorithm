#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <windows.h> // QueryPerformace需要
using namespace std;

// 定義 Array 結構，用來存堆排序的資料
struct Array {
    int heap_size = 0; // 堆的大小
    vector<int> v;
};

// 合併排序的合併步驟，將兩個已排序的子陣列合併
void merge_combine(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // 左半部大小
    int n2 = right - mid;    // 右半部大小

    int* L = new int[n1 + 1]; // 左半部臨時陣列，多一個位置放 MAX
    int* R = new int[n2 + 1]; // 右半部臨時陣列，多一個位置放 MAX

    L[n1] = INT_MAX; // 確保合併時不會越界
    R[n2] = INT_MAX;

    // 將 arr 的左半部和右半部複製到臨時陣列
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合併：比較 L 和 R 的元素，依序放回 arr
    int i = 0, j = 0, k = left;
    while (i < n1 || j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    delete[] L; // 釋放記憶體
    delete[] R;
}

// 合併排序的分割步驟：遞迴分割陣列
void merge_divide(vector<int>& arr, int left, int right) {
    int mid = left + (right - left) / 2; // 計算中間點，避免整數溢出
    if (left < right) {
        merge_divide(arr, left, mid);      // 遞迴處理左半部
        merge_divide(arr, mid + 1, right); // 遞迴處理右半部
        merge_combine(arr, left, mid, right); // 合併結果
    }
}

// 執行合併排序並測量時間
void merge(vector<int> arr, int size) {
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq); // 取得計時器頻率
    QueryPerformanceCounter(&nBeginTime); // 開始計時

    merge_divide(arr, 0, size - 1); // 執行合併排序

    QueryPerformanceCounter(&nEndTime); // 停止計時
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
    cout << fixed << setprecision(6) << "Merge Sort Time : " << time << " seconds" << endl;
}

// 執行插入排序並測量時間
void insertion(vector<int> arr, int size) {
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq); // 取得計時器頻率
    QueryPerformanceCounter(&nBeginTime); // 開始計時

    for (int i = 1; i < size; i++) {
        int key = arr[i]; // 當前要插入的元素
        int j = i - 1;
        // 將比 key 大的元素往後移
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // 插入 key 到正確位置
    }

    QueryPerformanceCounter(&nEndTime); // 停止計時
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
    cout << fixed << setprecision(6) << "Insertion Sort Time : " << time << " seconds" << endl;
}

// 調整函數，維護最大堆性質
void Max_heapify(Array& a, int i) {
    int l = 2 * i + 1; // 左子節點
    int r = 2 * i + 2; // 右子節點
    int largest = i;   // 假設當前節點最大
    if (l < a.heap_size && a.v[l] > a.v[i]) {
        largest = l; // 更新最大值為左子節點
    }
    if (r < a.heap_size && a.v[r] > a.v[largest]) {
        largest = r; // 更新最大值為右子節點
    }
    if (largest != i) {
        swap(a.v[i], a.v[largest]); // 交換，使父節點最大
        Max_heapify(a, largest);    // 遞迴調整受影響的子樹
    }
}

// 建立最大堆
void Build_max_heap(Array& a) {
    a.heap_size = a.v.size(); // 設定堆大小
    for (int i = (a.v.size() - 1) / 2; i >= 0; i--) {
        Max_heapify(a, i); // 從最後一個非葉節點開始調整
    }
}

// 執行堆排序並測量時間
void Heapsort(Array& a) {
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq); // 取得計時器頻率
    QueryPerformanceCounter(&nBeginTime); // 開始計時
    Build_max_heap(a); // 建立最大堆
    for (int i = a.v.size() - 1; i >= 1; i--) {
        swap(a.v[0], a.v[i]); // 將最大值放到陣列末尾
        a.heap_size--;        // 減少堆大小
        Max_heapify(a, 0);    // 調整堆
    }
    QueryPerformanceCounter(&nEndTime); // 停止計時
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
    cout << fixed << setprecision(6) << "Heap Sort Time : " << time << " seconds" << endl;
}

// 生成隨機陣列並測試三種排序演算法
int main() {
    srand(time(NULL)); // 初始化隨機變數
    int size;
    while (cout << "Please enter the size of an array : ", cin >> size) { // eof 輸入

        if (size == 0)
            break;

        vector<int> arr(size); // 建立指定大小的陣列
        Array a;

        for (int i = 0; i < size; i++) {
            arr[i] = rand() % size; // 填入隨機數
            a.v.push_back(arr[i]);
        }

        Heapsort(a);    // 執行堆排序
        insertion(arr, size); // 執行插入排序
        merge(arr, size);     // 執行合併排序

        // for(auto it : a.v)
        // {
        //     cout << it << " " ;
        // }

        cout << "______________________________________________" << endl;
    }
    return 0;
}