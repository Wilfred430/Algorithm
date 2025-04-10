#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> v; // 定義一個全域變數向量，用來存放輸入的數列

// 合併函數，將兩個已排序的子數列合併成一個
void Merge(int left, int right, int mid)
{
	int n1 = mid - left + 1; // 左半部分的長度
	int n2 = right - mid;	 // 右半部分的長度

	int *L = new int[n1 + 1]; // 分配內存給左半部分並多留一個位置給哨兵
	int *R = new int[n2 + 1]; // 分配內存給右半部分並多留一個位置給哨兵

	L[n1] = INT_MAX; // 使用最大整數作為哨兵，確保不會越界
	R[n2] = INT_MAX; // 使用最大整數作為哨兵，確保不會越界

	for (int i = 0; i < n1; i++) // 將左半部分的數據拷貝到數組 L 中
	{
		L[i] = v[left + i];
	}
	for (int i = 0; i < n2; i++) // 將右半部分的數據拷貝到數組 R 中
	{
		R[i] = v[mid + i + 1];
	}

	int i = 0, j = 0;					// 初始化 L 和 R 的索引
	for (int k = left; k <= right; k++) // 合併兩個子數列
	{
		if (L[i] <= R[j]) // 如果 L 的當前元素小於或等於 R 的當前元素
		{
			v[k] = L[i]; // 將 L 的元素放入結果數列
			i++;
		}
		else
		{
			v[k] = R[j]; // 將 R 的元素放入結果數列
			j++;
		}
	}

	delete[] L; // 釋放分配的內存
	delete[] R; // 釋放分配的內存
}

// 合併排序函數，對數列進行分治排序
void Merge_sort(int left, int right)
{
	if (left < right) // 當左指標小於右指標時，繼續分解
	{
		int mid = left + (right - left) / 2; // 計算中間位置，防止溢位
		Merge_sort(left, mid);				 // 遞迴地對左半部分進行排序
		Merge_sort(mid + 1, right);			 // 遞迴地對右半部分進行排序
		Merge(left, right, mid);			 // 合併排序後的兩個部分
	}
}

int main()
{
	int num;
	while (cin >> num) // 持續讀取輸入的數字數量
	{
		if (num == 0)
		{
			break; // 如果輸入為0則退出程式
		}
		v.clear(); // 清空向量
		int tmp;
		for (int i = 0; i < num; i++) // 讀取數字並加入向量
		{
			cin >> tmp;
			v.push_back(tmp);
		}

		Merge_sort(0, num - 1); // 對整個向量進行合併排序

		cout << "After sort : " << endl;
		for (auto it : v) // 輸出排序後的結果
		{
			cout << it << " ";
		}
		cout << endl; // 輸出換行符
	}

	return 0;
}
