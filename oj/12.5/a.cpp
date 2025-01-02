#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const pair<int, int> dirs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n;

int calIslandSurface(vector<vector<int>>& map, int x, int y, int id) {
    if (x < 0 || y < 0 || x >= n || y >= n || map[x][y] != 1) {
        return 0;
    }
    map[x][y] = id;
    int area = 1;
    for (auto each : dirs) {
        int nx = x + each.first;
        int ny = y + each.second;
        area += calIslandSurface(map, nx, ny, id);
    }
    return area;
}

int largestIsland(vector<vector<int>>& map) {
    unordered_map<int, int> area_map;
    int id = 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == 1) {
                int area = calIslandSurface(map, i, j, id);
                area_map[id++] = area;
            }
        }
    }

    int max_area = 0;
    for (const auto& entry : area_map) {
        max_area = std::max(entry.second, max_area);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!map[i][j]) {
                // 海
                unordered_set<int> neighbors;
                for (auto each : dirs) {
                    int nx = i + each.first;
                    int ny = j + each.second;
                    if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                        int nid = map[nx][ny];
                        if (nid > 1) {
                            neighbors.insert(nid);
                        }
                    }
                }
                int new_area = 1; // 当前填海的单元格
                for (const auto& nid : neighbors) {
                    new_area += area_map[nid];
                }
                max_area = std::max(max_area, new_area);
            }
        }
    }
    return max_area;
}

int main() {
    cin >> n;
    vector<vector<int>> map(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    cout << largestIsland(map);
    return 0;
}