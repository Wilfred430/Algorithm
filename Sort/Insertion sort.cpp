#include <iostream>
#include <vector>
using namespace std;

vector<int> v; // 定義一個全域變數向量，用來存放輸入的數列

// 插入排序函數
void insertion_sort()
{
	for (int i = 1; i < v.size(); i++) // 從數列的第二個元素開始遍歷
	{
		int key = v[i]; // 將當前元素作為"鑰匙"元素，準備插入到已排序部分
		int j = i - 1;	// 初始化 j 為 i 的前一個位置

		// 將已排序部分中大於 key 的元素右移一位
		while (j >= 0 && v[j] > key)
		{
			v[j + 1] = v[j]; // 向右移動元素
			j--;			 // 繼續向前比較
		}
		v[j + 1] = key; // 將 key 插入到正確的位置
	}
}

int main()
{
	int num;
	while (cin >> num) // 不斷讀取數字，直到輸入 0 為止
	{
		if (num == 0)
		{
			break; // 如果輸入 0，退出程式
		}
		v.clear(); // 清空向量以便存放新一輪的輸入數列
		int tmp;
		for (int i = 0; i < num; i++) // 將輸入的數字存入向量
		{
			cin >> tmp;
			v.push_back(tmp);
		}

		insertion_sort(); // 對數列進行插入排序

		cout << "After sort: ";
		for (auto it : v) // 輸出排序後的數列
		{
			cout << it << " ";
		}
		cout << endl; // 輸出換行符
	}

	return 0;
}
