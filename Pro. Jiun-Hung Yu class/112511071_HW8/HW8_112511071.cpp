/**
 * 毒菇森林冒險 - DFS實作
 * 
 * 基本規則：
 * 1. 每個冒險者從指定的森林入口出發，目標抵達寶藏地點
 * 2. 每移動一步都會消耗對應角色的基本移動生命值
 * 3. 踩到毒菇格子會額外扣除10點生命值
 * 4. 每個位置最多只能走一次，不可回頭
 * 5. 僅當成功抵達寶藏地點且生命值大於0才算一條合法路徑
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

vector<pair<int, int>> incline{{-1, 1}, {1, 1}, {-1, -1}, {1, -1}};
vector<pair<int, int>> straight{{1, 0}, {-1, 0}, {0, -1}, {0, 1}}; // 四個方向

/**
 * LUKA 的 DFS 遞迴搜尋函數
 * @param Graph: 地圖
 * @param visited: 訪問紀錄
 * @param x, y: 當前位置
 * @param end: 終點位置
 * @param health: 當前生命值
 * @param last_dir: 上一步的移動方向
 * @param path_count: 路徑計數器
 */

// LUKA 的 DFS 函數 - 遞歸實現
int DFS_LUKA_Helper(const vector<vector<int>> &Graph,
                    vector<vector<bool>> &visited,
                    int x, int y,
                    const pair<int, int> &end,
                    int health,
                    int last_dir,
                    int &path_count)
{

    // 如果路徑數已達上限，提前終止
    if (path_count >= 1000000)
    {
        return path_count;
    }

    // 到達終點且生命值 > 0
    if (x == end.first && y == end.second && health > 0)
    {
        path_count++;
        return path_count;
    }

    // 檢查四個方向
    for (int dir = 0; dir < 4; dir++)
    {
        // LUKA 不能連續朝同一方向移動
        if (dir == last_dir)
            continue;

        int nx = x + straight[dir].first;
        int ny = y + straight[dir].second;

        // 檢查邊界
        if (nx < 0 || nx >= Graph.size() || ny < 0 || ny >= Graph[0].size())
        {
            continue;
        }

        // 檢查是否為樹木或已訪問
        if (Graph[nx][ny] == 0 || visited[nx][ny])
        {
            continue;
        }

        // 計算移動後的生命值
        int new_health = health - 2; // 基本移動消耗
        if (Graph[nx][ny] == 2)
        { // 踩到毒菇額外扣除10點
            new_health -= 10;
        }

        // 如果不是終點但生命值已不足，跳過
        if (new_health <= 0)
        {
            continue;
        }

        // 標記訪問並遞歸搜索
        visited[nx][ny] = true;
        DFS_LUKA_Helper(Graph, visited, nx, ny, end, new_health, dir, path_count);
        visited[nx][ny] = false; // 回溯
    }

    return path_count;
}

// LUKA 的 DFS 函數入口
int DFS_LUKA(const vector<vector<int>> &Graph,
             const pair<int, int> &start,
             const pair<int, int> &end)
{
    int m = Graph.size();
    int n = Graph[0].size();

    // 訪問矩陣
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    // 標記起點為已訪問
    visited[start.first][start.second] = true;

    int path_count = 0;

    // 開始DFS搜索，初始生命值100，無前一方向(-1)
    DFS_LUKA_Helper(Graph, visited, start.first, start.second,
                    end, 100, -1, path_count);

    return min(path_count, 1000000);
}

/**
 * FIZZ 的 DFS 搜尋實作
 * 特性：
 * 1. 只能斜向移動，每步消耗1點生命值
 * 2. 必須優先訪問毒菇
 * 3. 如果周圍有未走過的路和已走過的毒菇，則路徑失敗
 * 4. 起始生命值50點
 * 
 * @param Graph: 地圖矩陣，0表示樹木，1表示普通路徑，2表示毒菇
 * @param visited: 訪問記錄矩陣
 * @param x, y: 當前位置
 * @param end: 終點位置
 * @param health: 當前生命值
 * @param path_count: 有效路徑計數
 */

// FIZZ 的 DFS 搜尋實作
int DFS_FIZZ_Helper(const vector<vector<int>> &Graph,
                    vector<vector<bool>> &visited,
                    int x, int y,
                    const pair<int, int> &end,
                    int health,
                    int &path_count)
{
    // 如果路徑數已達上限，提前終止
    if (path_count >= 1000000)
        return path_count;

    // 到達終點且生命值 > 0
    if (x == end.first && y == end.second && health > 0)
    {
        path_count++;
        return path_count;
    }

    // 先檢查是否有可以訪問的毒菇
    bool found_mushroom = false;

    // 第一階段：檢查和訪問毒菇
    for (int dir = 0; dir < 4; dir++)
    {
        int nx = x + incline[dir].first;
        int ny = y + incline[dir].second;

        // 檢查邊界
        if (nx < 0 || nx >= Graph.size() || ny < 0 || ny >= Graph[0].size())
            continue;

        // 檢查是否為未訪問的毒菇
        if (Graph[nx][ny] == 2 && !visited[nx][ny])
        {
            found_mushroom = true;
            int new_health = health - 11; // 斜向移動(1) + 毒菇懲罰(10)

            if (new_health > 0)
            {
                visited[nx][ny] = true;
                DFS_FIZZ_Helper(Graph, visited, nx, ny, end, new_health, path_count);
                visited[nx][ny] = false;
            }
        }
    }

    // 第二階段：如果沒有找到可訪問的毒菇，嘗試普通移動
    if (!found_mushroom)
    {

        // 進行普通移動
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = x + incline[dir].first;
            int ny = y + incline[dir].second;

            // 檢查邊界和可行性
            if (nx < 0 || nx >= Graph.size() || ny < 0 || ny >= Graph[0].size())
                continue;

            // 檢查是否為可行路徑且未訪問
            if (Graph[nx][ny] >= 1 && !visited[nx][ny])
            {
                int new_health = health - 1; // 斜向移動消耗1點生命值

                if (new_health > 0)
                {
                    visited[nx][ny] = true;
                    DFS_FIZZ_Helper(Graph, visited, nx, ny, end, new_health, path_count);
                    visited[nx][ny] = false;
                }
            }
        }
    }

    return path_count;
}

int DFS_FIZZ(const vector<vector<int>> &Graph,
             const pair<int, int> &start,
             const pair<int, int> &end)
{
    int m = Graph.size();
    int n = Graph[0].size();

    // 訪問矩陣
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    // 標記起點為已訪問
    visited[start.first][start.second] = true;

    int path_count = 0;

    // 開始DFS搜索，初始生命值100，無前一方向(-1)
    DFS_FIZZ_Helper(Graph, visited, start.first, start.second,
                    end, 50, path_count);

    return min(path_count, 1000000);
}

/**
 * JOJO 的 DFS 搜尋實作
 * 特性：
 * 1. 可以直線移動，每步消耗3點生命值
 * 2. 可以啟動替身狀態，持續3回合
 * 3. 替身狀態可以走任何格子且不消耗生命值
 * 4. 起始生命值100點
 * 
 * @param stand_turns: 替身剩餘回合數
 * @param stand_used: 是否已使用過替身能力
 */

// JOJO 的 DFS 搜尋實作
int DFS_JOJO_Helper(const vector<vector<int>> &Graph,
                    vector<vector<bool>> &visited,
                    int x, int y,
                    const pair<int, int> &end,
                    int health,
                    int stand_turns,
                    bool stand_used,
                    int &path_count)
{
    // 如果路徑數已達上限，提前終止
    if (path_count >= 1000000)
        return path_count;

    // 到達終點且生命值 > 0
    if (x == end.first && y == end.second && health > 0)
    {
        path_count++;
        return path_count;
    }

    // 遍歷四個方向
    for (const auto &dir : straight)
    {
        int nx = x + dir.first;
        int ny = y + dir.second;

        // 檢查邊界和是否已訪問
        if (nx < 0 || nx >= Graph.size() || ny < 0 || ny >= Graph[0].size() || visited[nx][ny])
            continue;

        // 替身狀態處理
        if (stand_turns > 0)
        {
            // 替身狀態可以走任何格子且不消耗生命值
            visited[nx][ny] = true;
            DFS_JOJO_Helper(Graph, visited, nx, ny, end, health,
                            stand_turns - 1, true, path_count);
            visited[nx][ny] = false;
        }
        else
        {
            // 可以選擇在這步啟動替身
            if (!stand_used && health > 0)
            {
                visited[nx][ny] = true;
                DFS_JOJO_Helper(Graph, visited, nx, ny, end, health,
                                2, true, path_count);
                visited[nx][ny] = false;
            }

            // 正常移動處理
            if (Graph[nx][ny] == 0)  // 不能走到樹木
                continue;

            // 計算新的生命值
            int new_health = health - 3;  // 基本移動消耗
            if (Graph[nx][ny] == 2)      // 踩到毒菇
            {
                new_health -= 10;
            }

            // 如果生命值足夠，繼續移動
            if (new_health > 0)
            {
                visited[nx][ny] = true;
                DFS_JOJO_Helper(Graph, visited, nx, ny, end, new_health,
                                0, stand_used, path_count);
                visited[nx][ny] = false;
            }
        }
    }

    return path_count;
}

int DFS_JOJO(const vector<vector<int>> &Graph,
             const pair<int, int> &start,
             const pair<int, int> &end)
{
    vector<vector<bool>> visited(Graph.size(), vector<bool>(Graph[0].size(), false));
    visited[start.first][start.second] = true;
    int path_count = 0;

    // 開始DFS搜索，初始生命值100，非忍者模式，忍者次數0
    DFS_JOJO_Helper(Graph, visited, start.first, start.second, end, 100, false, 0, path_count);

    return min(path_count, 1000000);
}

int main()
{
    ifstream in("input_hw8.txt");
    ofstream out("112511071_output.txt");

    if (in.fail())
    {
        cerr << "Error to open input file !!!" << endl;
        return 0;
    }

    if (out.fail())
    {
        cerr << "Error to open output file !!!" << endl;
        return 0;
    }

    string role;
    int row, col;
    pair<int, int> start, end;
    while (in >> role)
    {
        in >> row >> col;
        in >> start.first >> start.second;
        in >> end.first >> end.second;

        vector<vector<int>> Graph(row, vector<int>(col, 0));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                in >> Graph[i][j];
            }
        }

        if (role == "luka")
        {
            out << DFS_LUKA(Graph, start, end) << endl;
        }
        else if (role == "fizz")
        {
            out << DFS_FIZZ(Graph, start, end) << endl;
        }
        else
        {
            out << DFS_JOJO(Graph, start, end) << endl;
        }
    }

    in.close();
    out.close();

    return 0;
}