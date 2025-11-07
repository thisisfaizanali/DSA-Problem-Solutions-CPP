/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;

// Memoization :
class Solution
{
private:
    int solve(int i, vector<int> &arr, int k, vector<int> &dp)
    {
        if (i == arr.size())
            return 0;
        if (dp[i] != -1)
            return dp[i];
        int sum = 0, maxi = -1e9, len = 0, maxSum = -1e9;
        // try every possible partition starting at index i and ending at most k elements ahead
        for (int j = i; j < min((int)arr.size(), i + k); ++j)
        {
            len++;                                       // current partition length
            maxi = max(maxi, arr[j]);                    // track maximum in this partition
            sum = len * maxi + solve(j + 1, arr, k, dp); // total = partition sum + best from remaining elements
            maxSum = max(maxSum, sum);                   // update best achievable sum from index i
        }
        return dp[i] = maxSum; // memoize result
    }

public:
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        int n = arr.size();
        vector<int> dp(n + 1, -1);
        return solve(0, arr, k, dp);
    }
};

// Tabulation :
class Solution
{
public:
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        int n = arr.size();
        vector<int> dp(n + 1, -1e9);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            int sum = 0, maxSum = -1e9, maxi = -1e9;
            // explore partitions starting at i up to length k
            for (int j = i; j < min(n, i + k); ++j)
            {
                maxi = max(maxi, arr[j]);     // update partition max
                int len = j - i + 1;          // partition length
                sum = maxi * len + dp[j + 1]; // total = partition contribution + optimal future result
                maxSum = max(maxSum, sum);    // track best sum for this starting index
                dp[i] = max(dp[i], maxSum);   // store in dp table
            }
        }
        return dp[0]; // final answer: best sum from index 0
    }
};
