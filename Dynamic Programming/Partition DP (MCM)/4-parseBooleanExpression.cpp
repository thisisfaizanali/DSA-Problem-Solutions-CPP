/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;

// Memoization :
class Solution
{
private:
    int solve(int i, int j, int isTrue, string &s, vector<vector<vector<int>>> &dp)
    {
        // Invalid substring (no valid expression)
        if (i > j)
            return 0;

        // Base case: single symbol (either 'T' or 'F')
        if (i == j)
        {
            if (isTrue)
                return s[i] == 'T'; // Return 1 if symbol is 'T' and we want True
            else
                return s[i] == 'F'; // Return 1 if symbol is 'F' and we want False
        }

        // If already computed, return stored value
        if (dp[i][j][isTrue] != -1)
            return dp[i][j][isTrue];

        int ways = 0; // Count total valid parenthesizations

        // Partition at every operator between i and j
        for (int k = i + 1; k < j; k += 2)
        {
            char op = s[k]; // Current operator

            // Recurse for left and right subexpressions (both True and False)
            int lT = solve(i, k - 1, true, s, dp);
            int lF = solve(i, k - 1, false, s, dp);

            int rT = solve(k + 1, j, true, s, dp);
            int rF = solve(k + 1, j, false, s, dp);

            // Combine results based on operator and desired result (isTrue)
            if (op == '&')
            {
                if (isTrue)
                    ways += lT * rT; // True only if both True
                else
                    ways += lF * rF + lF * rT + lT * rF; // All other combos = False
            }
            else if (op == '|')
            {
                if (isTrue)
                    ways += lT * rF + lF * rT + lT * rT; // True if any side True
                else
                    ways += lF * rF; // False only if both False
            }
            else if (op == '^')
            {
                if (isTrue)
                    ways += lT * rF + lF * rT; // True if one True, one False
                else
                    ways += lF * rF + lT * rT; // False if both same
            }
        }

        // Store computed result and return
        return dp[i][j][isTrue] = ways;
    }

public:
    int countWays(string &s)
    {
        int n = s.size();
        // 3D DP array: dp[i][j][0] = ways to make false, dp[i][j][1] = ways to make true
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2, -1)));
        return solve(0, n - 1, 1, s, dp); // Evaluate full string to True
    }
};