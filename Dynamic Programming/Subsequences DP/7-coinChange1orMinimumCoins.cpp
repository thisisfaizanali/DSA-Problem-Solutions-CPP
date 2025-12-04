/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;

// Memoization :
class Solution
{
private:
    int solve(int i, int amount, vector<vector<int>> &dp, vector<int> &coins)
    {
        if (amount == 0) // base case: if target amount is 0, no coins are needed
            dp[i][0] = 0;

        if (i == 0) // base case: only the first coin is available
        {
            if (amount % coins[0] == 0)   // if amount can be made with multiples of coin[0]
                return amount / coins[0]; // return the number of coins required
            else
                return 1e9; // impossible to form amount
        }

        if (dp[i][amount] != -1) // return already computed state
            return dp[i][amount];

        // Option 1: pick current coin (stay on same index since unlimited coins allowed)
        int pick = (coins[i] <= amount) ? 1 + solve(i, amount - coins[i], dp, coins) : 1e9;
        // Option 2: do not pick current coin (move to previous index)
        int notPick = solve(i - 1, amount, dp, coins);

        // Store and return minimum of both options
        return dp[i][amount] = min(pick, notPick);
    }

public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        // initialize dp with -1 (uncomputed states)
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        int ans = solve(n - 1, amount, dp, coins);
        return ans >= 1e9 ? -1 : ans; // return -1 if impossible
    }
};

// Tabulation :
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        // dp[i][a] = minimum coins required to form amount `a` using coins[0..i]
        vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

        // base case: to form 0 amount, 0 coins are needed
        for (int i = 0; i < n; ++i)
            dp[i][0] = 0;

        // base case: with only the first coin
        for (int a = 0; a <= amount; ++a)
            dp[0][a] = (a % coins[0] == 0) ? a / coins[0] : 1e9;

        // fill dp table
        for (int i = 1; i < n; ++i)
        {
            for (int a = 0; a <= amount; ++a)
            {
                // pick current coin (stay in same row since unlimited use allowed)
                int pick = (coins[i] <= a) ? 1 + dp[i][a - coins[i]] : 1e9;
                // do not pick current coin (use previous row)
                int notPick = dp[i - 1][a];
                // take minimum
                dp[i][a] = min(pick, notPick);
            }
        }
        // final answer in bottom-right cell, -1 if impossible
        return dp[n - 1][amount] >= 1e9 ? -1 : dp[n - 1][amount];
    }
};

// Space optimization :
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        // prev = dp[i-1], curr = dp[i]
        vector<int> prev(amount + 1, 0), curr(amount + 1, 0);

        // base case: to form 0 amount, 0 coins are needed
        prev[0] = 0;

        // base case: with only the first coin
        for (int a = 0; a <= amount; ++a)
            prev[a] = (a % coins[0] == 0) ? a / coins[0] : 1e9;

        // process coins from 2nd to last
        for (int i = 1; i < n; ++i)
        {
            for (int a = 0; a <= amount; ++a)
            {
                // pick current coin (stay in curr row since unlimited use allowed)
                int pick = (coins[i] <= a) ? 1 + curr[a - coins[i]] : 1e9;
                // do not pick current coin (take from prev row)
                int notPick = prev[a];
                curr[a] = min(pick, notPick);
            }
            prev = curr; // move current row to prev for next iteration
        }

        // answer in prev[amount], -1 if impossible
        return prev[amount] >= 1e9 ? -1 : prev[amount];
    }
};
