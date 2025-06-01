// Problem: Number of Ways to Assign Edge Weights I
// Leetcode-style Tree + CP Observation Based Solution

/*
💡 PROBLEM STATEMENT:

You are given an undirected tree rooted at node 1 with 'n' nodes.
Each edge initially has weight 0, but you must assign each edge a weight of either 1 or 2.

The cost of a path between any two nodes is defined as the sum of edge weights in the path.

👉 Goal: 
Pick any one node x at the maximum depth (i.e., farthest from node 1), and return the number of ways to assign weights {1, 2} to the path from node 1 to x such that the total cost is ODD.

📌 Since answer can be large, return it modulo 10^9 + 7.

---------------------
🔎 OBSERVATION:

Let the depth of the selected node x from node 1 be 'd'.
This means the path from 1 to x contains exactly 'd' edges.

Each edge can be either:
- 1 (odd contribution)
- 2 (even contribution)

So, for 'd' edges:
- Total combinations = 2^d
- Half of these will give ODD total weight (cost)
  ➝ because combinations with **odd number of 1s** result in odd sum

🧠 Therefore, valid combinations = 2^(d - 1)

---------------------
✅ EXAMPLES:

- edges = [[1, 2]]
  → depth = 1 → Answer = 2^(1-1) = 1

- edges = [[1,2],[1,3],[3,4],[3,5]]
  → max depth = 2 → Answer = 2^(2-1) = 2

---------------------
🛠 APPROACH:

1. Build the tree using adjacency list
2. Use DFS to calculate maximum depth from root (node 1)
3. Use fast exponentiation to compute 2^(depth - 1) % MOD
*/

class Solution {
public:
    const int MOD = 1e9 + 7; // Modulo as per problem constraints

    // Fast exponentiation function to compute (a^b) % MOD
    int power(int a, int b) {
        long long res = 1;
        long long base = a;

        while (b > 0) {
            if (b % 2 == 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            b /= 2;
        }
        return res;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size() + 1; // Since there are n-1 edges in a tree with n nodes

        // Step 1: Build adjacency list for the tree
        vector<vector<int>> adj(n + 1); // 1-indexed nodes
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Step 2: Find maximum depth from node 1 using DFS
        int maxDepth = 0;
        vector<bool> visited(n + 1, false);

        function<void(int, int)> dfs = [&](int node, int depth) {
            visited[node] = true;
            maxDepth = max(maxDepth, depth);

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    dfs(neighbor, depth + 1);
                }
            }
        };

        dfs(1, 0); // Start DFS from root node (1) with depth 0

        // Step 3: Apply CP trick → number of valid assignments = 2^(depth - 1)
        return power(2, maxDepth - 1);
    }
};
