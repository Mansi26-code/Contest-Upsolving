// You are given a 2D grid of integers.
// Return true if the grid can be partitioned either horizontally or vertically into two equal-sum parts.

TC=O(m*n)
SC=O(m+n)


class Solution {
    public:
        // Function to check if a vertical partition (column-wise) exists with equal sum
        bool checkVertical(vector<vector<int>>& grid) {
            int m = grid.size();        // number of rows
            int n = grid[0].size();     // number of columns
    
            // Step 1: Calculate column-wise total sum
            vector<long long> colSum(n, 0);
            for (int j = 0; j < n; j++) {
                for (int i = 0; i < m; i++) {
                    colSum[j] += grid[i][j];
                }
            }
    
            // Step 2: Build prefix sum for columns
            vector<long long> prefix(n, 0);
            prefix[0] = colSum[0];
            for (int i = 1; i < n; i++) {
                prefix[i] = prefix[i - 1] + colSum[i];
            }
    
            long long total = prefix[n - 1]; // Total sum of all columns
    
            // Step 3: Check if there's a split where left == right
            for (int i = 0; i < n - 1; i++) {
                long long left = prefix[i];
                long long right = total - left;
                if (left == right) return true;
            }
    
            return false;
        }
    
        // Function to check if a horizontal partition (row-wise) exists with equal sum
        bool checkHorizontal(vector<vector<int>>& grid) {
            int m = grid.size();        // number of rows
            int n = grid[0].size();     // number of columns
    
            // Step 1: Calculate row-wise total sum
            vector<long long> rowSum(m, 0);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    rowSum[i] += grid[i][j];
                }
            }
    
            // Step 2: Build prefix sum for rows
            vector<long long> prefix(m, 0);
            prefix[0] = rowSum[0];
            for (int i = 1; i < m; i++) {
                prefix[i] = prefix[i - 1] + rowSum[i];
            }
    
            long long total = prefix[m - 1]; // Total sum of all rows
    
            // Step 3: Check if there's a split where top == bottom
            for (int i = 0; i < m - 1; i++) {
                long long top = prefix[i];
                long long bottom = total - top;
                if (top == bottom) return true;
            }
    
            return false;
        }
    
        // Main function to check if grid can be partitioned
        bool canPartitionGrid(vector<vector<int>>& grid) {
            return checkVertical(grid) || checkHorizontal(grid);
        }
    };

    

    //Brute

    class Solution {
        public:
            // Helper to compute sum from column 'start' to 'end' across all rows
            long long summ(int start, int end, vector<vector<int>>& grid) {
                long long sum = 0;
                int m = grid.size();
                for (int i = 0; i < m; i++) {
                    for (int j = start; j <= end; j++) {
                        sum += grid[i][j];
                    }
                }
                return sum;
            }
        
            // Check if a vertical split exists (column-wise) with equal sum on both sides
            bool checkVertical(vector<vector<int>>& grid) {
                int n = grid[0].size(); // number of columns
        
                // Try every vertical split position
                for (int i = 0; i < n - 1; i++) {
                    long long sum1 = summ(0, i, grid);       // sum of columns from 0 to i
                    long long sum2 = summ(i + 1, n - 1, grid); // sum of columns from i+1 to end
                    if (sum1 == sum2) return true;
                }
        
                return false;
            }
        
            // Helper to compute sum from row 'start' to 'end' across all columns
            long long summHorizontal(int start, int end, vector<vector<int>>& grid) {
                long long sum = 0;
                int n = grid[0].size();
                for (int i = start; i <= end; i++) {
                    for (int j = 0; j < n; j++) {
                        sum += grid[i][j];
                    }
                }
                return sum;
            }
        
            // Check if a horizontal split exists (row-wise) with equal sum on both sides
            bool checkHorizontal(vector<vector<int>>& grid) {
                int m = grid.size(); // number of rows
        
                // Try every horizontal split position
                for (int i = 0; i < m - 1; i++) {
                    long long sum1 = summHorizontal(0, i, grid);       // sum of rows from 0 to i
                    long long sum2 = summHorizontal(i + 1, m - 1, grid); // sum of rows from i+1 to end
                    if (sum1 == sum2) return true;
                }
        
                return false;
            }
        
            // Main function to check grid partitioning
            bool canPartitionGrid(vector<vector<int>>& grid) {
                return checkVertical(grid) || checkHorizontal(grid);
            }
        };

        TC= O((m + n) * m * n)
        SC=O(1)










        Intuition
// Look closely at input and output .Now you get that you need the find total sum of grid. After getting total grid sum You need to see if you can make line at every row for that calculate each row sum then check if(2horizontalsum==totalsum).After that check column wise but you cant directly do that like horizontal sum so make a vector and store column wise sum in it then do again check vertically if we can draw line if(2leftsum ==totalsum) .

// code

class Solution {
    public:
        bool canPartitionGrid(vector<vector<int>>& grid) {
            int row=grid.size();
            int col=grid[0].size();
            int rowhalf=row/2;
            long long totalsum=0;
            long long  horizontalsum=0; 
            long long verticalsum=0;
             // total sum of grid in sum
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    totalsum+=grid[i][j];
                }
            }
           
            for(int i=0;i<row-1;i++){
                for(int j=0;j<col;j++)
                    horizontalsum+=grid[i][j];
                if(2*horizontalsum==totalsum) return true;
                
            }
            vector<long long>colSum(col,0);{
            for(int i=0;i<col;i++){
                for(int j=0;j<row;j++)
                    colSum[i]+=grid[j][i];
                }
            }
            long long leftsum=0;
            for(int i=0;i<col-1;i++){           
                leftsum+=colSum[i];
                if(2*leftsum ==totalsum) return true;
                
            }
             return false;
                
            
        }
    };