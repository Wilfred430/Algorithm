#include <iostream>
#include <vector>
using namespace std;

vector<int> ans; 

bool LinearSearch(int target)
{
    for(int i=0; i < ans.size(); i++)
    {
        if(ans[i] == target)
        {
            cout << i+1 << endl; // 打印找到的元素的1-based索引
            return true;         // 返回 true 表示找到了目標元素
        }
    }

    return false; // 返回 false 表示沒有找到目標元素
}

int main()
{
    int num; // 數組中的元素個數
    while (cin >> num)
    {
        if (num == 0)
        {
            break; // 如果元素數量為零則退出循環
        }
        int tmp;         // 臨時變量用於存儲輸入值
        for (int i = 0; i < num; i++)
        {
            cin >> tmp;         // 讀取每個元素
            ans.push_back(tmp); // 將元素添加到向量中
        }

        cout << "Please enter a num which you want to search : ";
        cin >> tmp; // 讀取要查找的數字

        if(!LinearSearch(tmp))
        {
            cout << "Not find between the array." << endl; // 如果沒有找到目標元素，則打印消息
        }

        ans.clear(); // 清空向量以便下一次輸入
    }

    return 0;
}
