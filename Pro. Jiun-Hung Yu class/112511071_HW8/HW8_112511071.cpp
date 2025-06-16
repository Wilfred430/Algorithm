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

    // int m = Graph.size();
    // int n = Graph[0].size();

    // // 訪問矩陣
    // vector<vector<bool>> visited(m, vector<bool>(n, false));

    // // 標記起點為已訪問
    // visited[start.first][start.second] = true;

    // int path_count = 0;

    // // 開始DFS搜索，初始生命值100，無前一方向(-1)
    // DFS_LUKA_Helper(Graph, visited, start.first, start.second,
    //                 end, 100, -1, path_count);

    // return min(path_count, 1000000);

    return 0;
}

// bool checkSurroundings(const vector<vector<int>>& Graph,
//                       const vector<vector<bool>>& visited,
//                       int x, int y,
//                       bool& has_unvisited_mushroom,
//                       bool& has_visited_mushroom,
//                       bool& has_unvisited_path) {
//     has_unvisited_mushroom = false;
//     has_visited_mushroom = false;
//     has_unvisited_path = false;

//     // 檢查斜向移動
//     for (const auto& dir : incline) {
//         int nx = x + dir.first;
//         int ny = y + dir.second;

//         if (nx >= 0 && nx < Graph.size() && ny >= 0 && ny < Graph[0].size()) {
//             if (Graph[nx][ny] == 2) {  // 是毒菇
//                 if (!visited[nx][ny]) {
//                     has_unvisited_mushroom = true;
//                 } else {
//                     has_visited_mushroom = true;
//                 }
//             } else if (Graph[nx][ny] == 1 && !visited[nx][ny]) {  // 是未走過的路
//                 has_unvisited_path = true;
//             }
//         }
//     }
    
//     // 如果有未走過的路且只有已走過的毒菇，返回true表示需要終止搜索
//     return has_unvisited_path && !has_unvisited_mushroom && has_visited_mushroom;
// }

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

    // 檢查斜向移動是否能到達毒菇
    for (int dir = 0; dir < 4; dir++)
    {
        int nx = x + incline[dir].first;
        int ny = y + incline[dir].second;

        // 檢查邊界
        if (nx < 0 || nx >= Graph.size() || ny < 0 || ny >= Graph[0].size())
            continue;

        // 檢查是否為毒菇且未訪問
        if (Graph[nx][ny] == 2 && !visited[nx][ny])
        {
            found_mushroom = true;
            int new_health = health - 11; // 斜向移動消耗1點，毒菇消耗10點

            if (new_health > 0)
            {
                visited[nx][ny] = true;
                DFS_FIZZ_Helper(Graph, visited, nx, ny, end, new_health, path_count);
                visited[nx][ny] = false;
            }
        }
    }

    // 如果沒有找到可以訪問的毒菇，則嘗試普通移動
    if (!found_mushroom)
    {
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = x + incline[dir].first;
            int ny = y + incline[dir].second;

            // 檢查邊界
            if (nx < 0 || nx >= Graph.size() || ny < 0 || ny >= Graph[0].size())
                continue;

            // 檢查是否為可行路徑且未訪問
            if (Graph[nx][ny] >= 1 && !visited[nx][ny])
            {
                int new_health = health - 1; // 斜向移動只消耗1點生命值

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

    return 0;
}

// JOJO 的 DFS 搜尋實作
int DFS_JOJO_Helper(const vector<vector<int>> &Graph,
                    vector<vector<bool>> &visited,
                    int x, int y,
                    const pair<int, int> &end,
                    int health,
                    int stand_turns, // 替身剩餘回合數
                    bool stand_used, // 是否已使用過替身
                    int &path_count)
{
    // 提前終止條件
    if (path_count >= 1000000)
        return path_count;

    // 檢查是否到達終點
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

        if (nx < 0 || nx >= Graph.size() || ny < 0 || ny >= Graph[0].size() || visited[nx][ny])
            continue;

        // 處理替身狀態
        if (stand_turns > 0)
        {
            visited[nx][ny] = true;
            DFS_JOJO_Helper(Graph, visited, nx, ny, end, health,
                            stand_turns - 1, true, path_count);
            visited[nx][ny] = false;
        }
        else
        {
            if (!stand_used && health > 0)
            {
                visited[nx][ny] = true;
                DFS_JOJO_Helper(Graph, visited, nx, ny, end, health,
                                2, true, path_count);
                visited[nx][ny] = false;
            }
            // 正常移動
            if (Graph[nx][ny] == 0)
                continue;

            int new_health = health - 3;
            if (Graph[nx][ny] == 2)
            {
                new_health -= 10;
            }

            if (new_health > 0)
            {
                visited[nx][ny] = true;

                // 繼續正常移動
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
    ifstream in("C:/Algorithm/Pro. Jiun-Hung Yu class/112511071_HW8/input_hw8.txt");
    ofstream out("C:/Algorithm/Pro. Jiun-Hung Yu class/112511071_HW8/112511071_output.txt");

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