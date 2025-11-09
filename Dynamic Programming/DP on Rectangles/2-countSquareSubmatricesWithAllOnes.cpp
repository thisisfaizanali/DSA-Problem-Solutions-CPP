/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countSquares(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();          // Get number of rows (m) and columns (n)
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // Create a DP table initialized with 0s (size m+1 x n+1 for safe bounds)

        // Initialize the first column of dp with the first column of matrix
        for (int i = 0; i < m; ++i)
            dp[i][0] = matrix[i][0];

        // Initialize the first row of dp with the first row of matrix
        for (int j = 0; j < n; ++j)
            dp[0][j] = matrix[0][j];

        // Fill the rest of the DP table
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                    dp[i][j] = 0; // If cell value is 0, it can't form a square ending here
                else
                    // Otherwise, it forms a square — take the minimum of top, left, and top-left squares + 1
                    dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
            }
        }

        int squares = 0; // Variable to store total count of square submatrices

        // Sum up all dp[i][j] values to count total number of squares
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                squares += dp[i][j];
            }
        }

        return squares; // Return total count
    }
};
