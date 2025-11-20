/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;

// Memoization :
class Solution
{
private:
    int solve(int i, string &s, vector<int> &dp)
    {
        // Base case: if we reach end of string, no cuts/partitions left
        if (i == s.size())
            return 0;

        if (dp[i] != -1)
            return dp[i];

        int mini = 1e9;   // initialize minimum partitions to large number
        string temp = ""; // to build substring s[i..j]

        // Try every possible end index j from i..end
        for (int j = i; j < s.size(); ++j)
        {
            temp += s[j]; // expand current substring by including s[j]

            // if current substring s[i..j] is palindrome
            if (isPalindrome(temp))
            {
                // 1 + solve(j + 1, s, dp):
                // '1' → current palindromic block (partition) made here
                // 'solve(j + 1, s, dp)' → solve remaining substring after j
                // together count total partitions for s[i..n-1]
                int cost = 1 + solve(j + 1, s, dp);

                mini = min(mini, cost);
            }
        }

        return dp[i] = mini;
    }

private:
    bool isPalindrome(string &s)
    {
        int l = 0, r = s.size() - 1;
        while (l < r)
        {
            if (s[l++] != s[r--])
                return false;
        }
        return true;
    }

public:
    int minCut(string &s)
    {
        int n = s.size();
        vector<int> dp(n, -1); // dp[i] stores min partitions from i..end

        // solve(0) gives number of palindromic partitions
        // subtract 1 because cuts = partitions - 1
        int ans = solve(0, s, dp) - 1;

        // return minimum number of cuts
        return ans;
    }
};

// Tabulation :
class Solution
{
private:
    bool isPalindrome(string &s)
    {
        int l = 0, r = s.size() - 1;
        while (l < r)
        {
            if (s[l++] != s[r--])
                return false;
        }
        return true;
    }

public:
    int minCut(string &s)
    {
        int n = s.size();

        // dp[i] = min partitions needed for substring s[i..end]
        // initialize with large values
        vector<int> dp(n + 1, 1e9);

        // base case: dp[n] = 0 (no partitions needed after end)
        dp[n] = 0;

        // fill dp from end to start (bottom-up)
        for (int i = n - 1; i >= 0; --i)
        {
            string temp = ""; // build substring s[i..j]

            // try all possible end positions j
            for (int j = i; j < s.size(); ++j)
            {
                temp += s[j]; // add character to substring

                // if substring s[i..j] is palindrome
                if (isPalindrome(temp))
                {
                    // 1 + dp[j + 1]:
                    // '1' = one palindromic block formed here
                    // dp[j + 1] = partitions for remaining substring
                    int cost = 1 + dp[j + 1];

                    dp[i] = min(cost, dp[i]);
                }
            }
        }

        // dp[0] = total partitions for whole string
        // cuts = partitions - 1
        return dp[0] - 1;
    }
};

// Most optimal using Precomputed Palindrome Check using DP :
class Solution
{
public:
    int minCut(string &s)
    {
        int n = s.size();

        // Precompute all palindromes: pal[i][j] means s[i..j] is palindrome
        vector<vector<bool>> pal(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i; j < n; ++j)
            {
                // j - i < 2 → length 1 or 2 handled instantly; pal[i+1][j-1] → inner substring
                if (s[i] == s[j] && (j - i < 2 || pal[i + 1][j - 1]))
                    pal[i][j] = true;
            }
        }

        // dp[i] = min partitions needed for substring s[i..end]
        // initialize with large values
        vector<int> dp(n + 1, 1e9);

        // base case: dp[n] = 0 (no partitions needed after end)
        dp[n] = 0;

        // fill dp from end to start (bottom-up)
        for (int i = n - 1; i >= 0; --i)
        {
            // try all possible end positions j
            for (int j = i; j < s.size(); ++j)
            {
                // pal[i][j] → O(1) check using precomputed table (short-circuits full scan)
                if (pal[i][j])
                {
                    // 1 + dp[j + 1]:
                    // '1' = one palindromic block formed here
                    // dp[j + 1] = partitions for remaining substring
                    int cost = 1 + dp[j + 1];

                    dp[i] = min(cost, dp[i]);
                }
            }
        }

        // dp[0] = total partitions for whole string
        // cuts = partitions - 1
        return dp[0] - 1;
    }
};
