/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    void dfs(int i, int j, vector<vector<char>> &grid, vector<vector<int>> &vis)
    {
        int m = grid.size();
        int n = grid[0].size();

        // Mark the current cell as visited
        vis[i][j] = 1;

        // Directions: up, right, down, left
        int dx[4] = {-1, 0, +1, 0};
        int dy[4] = {0, +1, 0, -1};

        for (int dir = 0; dir < 4; ++dir)
        {
            int ni = i + dx[dir];
            int nj = j + dy[dir];

            // Check if the neighbor is within bounds, unvisited, and is land ('1')
            if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
                !vis[ni][nj] && grid[ni][nj] == '1')
            {
                dfs(ni, nj, grid, vis);
            }
        }
    }

public:
    int numIslands(vector<vector<char>> &grid)
    {
        // The number of connected components (islands) in the grid
        int numIslands = 0;
        int m = grid.size();
        int n = grid[0].size();

        // 2D visited array to track visited land cells
        vector<vector<int>> vis(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                // If the cell is unvisited and is land ('1'), start a DFS
                if (!vis[i][j] && grid[i][j] == '1')
                {
                    numIslands++;         // New island found
                    dfs(i, j, grid, vis); // Mark all connected land
                }
            }
        }
        return numIslands;
    }
};

// GFG version has 8 directions :
class Solution
{
private:
    void dfs(int i, int j, vector<vector<char>> &grid, vector<vector<int>> &vis)
    {
        int m = grid.size();
        int n = grid[0].size();
        vis[i][j] = 1;
        // 8 directions: vertical, horizontal, diagonal
        int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int dir = 0; dir < 8; ++dir)
        {
            int ni = i + dx[dir];
            int nj = j + dy[dir];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
                !vis[ni][nj] && grid[ni][nj] == 'L')
            {
                dfs(ni, nj, grid, vis);
            }
        }
    }

public:
    int countIslands(vector<vector<char>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vis(m, vector<int>(n, 0));
        int count = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (!vis[i][j] && grid[i][j] == 'L')
                {
                    ++count;
                    dfs(i, j, grid, vis);
                }
            }
        }
        return count;
    }
};
