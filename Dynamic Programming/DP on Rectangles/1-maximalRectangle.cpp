/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;

// Tagged DP because heights array is built using previous row values (DP relation)
class Solution
{
public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int maxArea = -1e9;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n); // DP array: cumulative heights of '1's column-wise
        for (int i = 0; i < m; ++i)
        {
            // Update histogram heights (DP step)
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == '1')
                    heights[j] += 1;
                else
                    heights[j] = 0;
            }
            // Compute max area for current histogram
            maxArea = max(maxArea, largestRectangle(heights));
        }
        return maxArea;
    }

private:
    int largestRectangle(vector<int> &heights)
    {
        int n = heights.size();
        int area = -1e9;
        stack<int> st; // Monotonic increasing stack (stores indices)
        for (int i = 0; i < n; ++i)
        {
            // Pop taller/equal bars → current i is Next Smaller Element (nse)
            while (!st.empty() && heights[st.top()] >= heights[i])
            {
                auto top = st.top();
                st.pop();
                int nse = i;                                      // current bar is first smaller → nse = i
                int pse = !st.empty() ? st.top() : -1;            // prev smaller to left or -1 if none
                area = max(area, heights[top] * (nse - pse - 1)); // area = height * width
            }
            st.push(i);
        }
        // Process remaining bars (nse = n → end of histogram)
        while (!st.empty())
        {
            auto top = st.top();
            st.pop();
            int nse = n;
            int pse = !st.empty() ? st.top() : -1;
            area = max(area, heights[top] * (nse - pse - 1));
        }
        return area;
    }
};