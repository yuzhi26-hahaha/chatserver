#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++; // 记录小于轴的位置的下一个位置
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // 获取基数位置
        quickSort(arr, low, pi - 1);        // 递归调用快排左边
        quickSort(arr, pi + 1, high);           // 右边
    }
}

int partition(vector<int>& arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(arr[j] < pivot){
            i++;        //记录基轴下一个应在的位置
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    vector<int> arr = {1, 543, 23, 24324, 2, 6, 87, 23, 6545, 65, 43, 23, 76, 87};
    quickSort(arr, 0, arr.size() - 1);
    for (int i = 0; i <= arr.size() - 1; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}


#include <vector>
#include <unordered_set>

using namespace std;

// Helper function to perform DFS and count reorientations
void dfs(int node, const vector<vector<int>>& graph, const unordered_set<int>& originalEdges, vector<bool>& visited, int& changes) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            // Check if the edge (node -> neighbor) is in the original edge set
            if (originalEdges.find(node * graph.size() + neighbor) == originalEdges.end()) {
                // This edge is not in the original direction, so it needs to be reoriented
                changes++;
            }
            dfs(neighbor, graph, originalEdges, visited, changes);
        }
    }
}

int minReorder(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);
    unordered_set<int> originalEdges;
    
    // Build the graph and store the original edges
    for (const auto& conn : connections) {
        graph[conn[0]].push_back(conn[1]);
        graph[conn[1]].push_back(conn[0]);
        originalEdges.insert(conn[0] * n + conn[1]);
    }
    
    vector<bool> visited(n, false);
    int changes = 0;
    
    // Start DFS from city 0
    dfs(0, graph, originalEdges, visited, changes);
    
    return changes;
}


class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        int m = maze.size();
        int n = maze[0].size();
        int step = 0;
        vector < vector<bool>> visited(m, vector<bool>(n, false));
        visited[entrance[0]][entrance[1]] = true;
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto& curr = q.front();
                q.pop();
                int x = curr.first, y = curr.second;
                if((x != entrance[0] || y != entrance[1]) && (x == 0 || x == m - 1 || y == 0 || y == n - 1)){
                    return step;
                }
                for (auto dir : directions) {
                    int cx = x + dir[0];
                    int cy = y + dir[1];
                    if (cx >= 0 && cx < m && cy >= 0 && cy < n &&
                        maze[cx][cy] == '.' && !visited[cx][cy]) {
                        q.push({cx, cy});
                        visited[cx][cy] = true;
                    }
                }
            }
            step++;
        }
        return -1;
    }
};

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        q.push({entrance[0], entrance[1]});
        visited[entrance[0]][entrance[1]] = true;
        int step = 0;

        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i < size; i++){
                pair<int, int> curr = q.front();
                q.pop();
                int x = curr.first;
                int y = curr.second;

                if((x != entrance[0] || y != entrance[1]) && (x == 0 || y == 0 || x == m - 1 || y == n - 1)){
                    return step;
                }

                for(auto dir : directions){
                    int nx = x + dir[0];
                    int ny = y + dir[1];
                    if(nx >= 0 && nx <= m - 1 && ny >= 0 && ny <= n - 1 && maze[nx][ny] == '.' && !visited[nx][ny]){
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }
            step++;
        }
        return -1;
    }

};