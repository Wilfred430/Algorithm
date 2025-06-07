#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

// 使用BFS移除與指定座標(x,y)相連的陸地
void EraseLand(vector<vector<int>> &G, int x, int y)
{
    queue<pair<int, int>> q;
    q.push({x, y});  // 將起始點加入佇列

    while (!q.empty())
    {
        pair<int, int> tmp = q.front();
        q.pop();

        // 檢查上方相鄰的陸地
        if (tmp.first - 1 >= 0 && G[tmp.first - 1][tmp.second] == 1)
        {
            q.push({tmp.first - 1, tmp.second});
            G[tmp.first - 1][tmp.second] = 0;  // 將陸地轉為海洋
        }
        // 檢查下方相鄰的陸地
        if (tmp.first + 1 < 8 && G[tmp.first + 1][tmp.second] == 1)
        {
            q.push({tmp.first + 1, tmp.second});
            G[tmp.first + 1][tmp.second] = 0;
        }
        // 檢查左方相鄰的陸地
        if (tmp.second - 1 >= 0 && G[tmp.first][tmp.second - 1] == 1)
        {
            q.push({tmp.first, tmp.second - 1});
            G[tmp.first][tmp.second - 1] = 0;
        }
        // 檢查右方相鄰的陸地
        if (tmp.second + 1 < 8 && G[tmp.first][tmp.second + 1] == 1)
        {
            q.push({tmp.first, tmp.second + 1});
            G[tmp.first][tmp.second + 1] = 0;
        }
    }
}

// 使用BFS計算島嶼數量
int BFS(vector<vector<int>> &G)
{
    int num = 0;  // 記錄島嶼數量
    vector<vector<int>> Visited(8, vector<int>(8, false));  // 記錄已訪問的位置
    queue<pair<int, int>> q;

    // 從(0,0)開始搜尋
    q.push({0, 0});
    Visited[0][0] = true;

    while (!q.empty())
    {
        pair<int, int> tmp = q.front();
        q.pop();

        // 檢查四個方向的相鄰位置
        // 上
        if (tmp.first - 1 >= 0 && !Visited[tmp.first - 1][tmp.second])
        {
            q.push({tmp.first - 1, tmp.second});
            Visited[tmp.first - 1][tmp.second] = true;
        }
        // 下
        if (tmp.first + 1 < 8 && !Visited[tmp.first + 1][tmp.second])
        {
            q.push({tmp.first + 1, tmp.second});
            Visited[tmp.first + 1][tmp.second] = true;
        }
        // 左
        if (tmp.second - 1 >= 0 && !Visited[tmp.first][tmp.second - 1])
        {
            q.push({tmp.first, tmp.second - 1});
            Visited[tmp.first][tmp.second - 1] = true;
        }
        // 右
        if (tmp.second + 1 < 8 && !Visited[tmp.first][tmp.second + 1])
        {
            q.push({tmp.first, tmp.second + 1});
            Visited[tmp.first][tmp.second + 1] = true;
        }

        // 如果當前位置是陸地，計數加1並移除這座島
        if (G[tmp.first][tmp.second] == 1)
        {
            num++;
            EraseLand(G, tmp.first, tmp.second);
        }
    }

    return num;
}

int main()
{
    // 讀取檔案
    string File;
    cout << "Enter the filename: ";
    cin >> File;

    // 開啟檔案並檢查是否成功
    ifstream in(File);
    if (in.fail())
    {
        cerr << "Can't open the file !!!" << endl;
        return 0;
    }

    // 處理每一個測試案例
    int pattern_num = 1;
    while (!in.eof())
    {
        // 讀取8x8的地圖
        vector<vector<int>> G(8, vector<int>(8, 0));
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                in >> G[i][j];
            }
        }

        // 輸出結果
        cout << "Number of Islands(Pattern" << pattern_num << "): " << BFS(G) << endl;
        pattern_num++;
    }

    // 關閉檔案
    in.close();

    return 0;
}
