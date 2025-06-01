class Solution {
public:
    // Function to find the maximum number of non-intersecting valid substrings
    int maxSubstrings(string word) {
        int n = word.size();
        vector<int> first(26, n), last(26, -1);

        // Step 1: Record first and last occurrence of every character
        for (int i = 0; i < n; ++i) {
            int idx = word[i] - 'a';
            first[idx] = min(first[idx], i);
            last[idx] = max(last[idx], i);
        }

        // Step 2: Generate candidate intervals [start, end] for valid substrings
        vector<pair<int, int>> intervals;

        for (int i = 0; i < 26; ++i) {
            if (first[i] < n) {
                int start = first[i], end = last[i];
                bool valid = true;

                // Check if entire substring contains only letters whose first/last are within this interval
                for (int j = start; j <= end && valid; ++j) {
                    int ch = word[j] - 'a';
                    if (first[ch] < start || last[ch] > end)
                        valid = false;
                }

                // Accept only valid and length >= 4 substrings
                if (valid && (end - start + 1) >= 4) {
                    intervals.emplace_back(start, end);
                }
            }
        }

        // Step 3: Greedily select non-overlapping substrings using interval scheduling
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
            return a.second < b.second; // sort by end time
        });

        int count = 0, prevEnd = -1;
        for (auto &[start, end] : intervals) {
            if (start > prevEnd) {
                count++;
                prevEnd = end;
            }
        }

        return count;
    }
};
