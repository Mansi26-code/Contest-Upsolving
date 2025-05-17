// Given a string s and an integer k, delete the minimum number of characters so that the string contains at most k distinct characters.
// Return the minimum number of deletions required to achieve this.


class Solution {
    public:
        int minDeletion(string s, int k) {
            // Step 1: Count frequency of each character in the string
            unordered_map<char, int> freq;
            for (char ch : s) {
                freq[ch]++;
            }
    
            // Step 2: If number of distinct characters ≤ k, no deletion is needed
            if (freq.size() <= k) return 0;
    
            // Step 3: Store all character frequencies into a vector for sorting
            vector<int> freqs;
            for (auto& it : freq) {
                freqs.push_back(it.second);
            }
    
            // Step 4: Sort frequencies in ascending order to remove least frequent characters first
            sort(freqs.begin(), freqs.end());
    
            // Step 5: Calculate how many distinct characters we need to remove
            int deletions = 0;
            int to_remove = freq.size() - k;
    
            // Step 6: Remove the 'to_remove' least frequent characters and add their counts to deletions
            for (int i = 0; i < to_remove; i++) {
                deletions += freqs[i];
            }
    
            // Step 7: Return the minimum deletions needed
            return deletions;
        }
    };
    