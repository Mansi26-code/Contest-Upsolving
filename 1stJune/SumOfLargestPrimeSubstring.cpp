class Solution {
public:
    // Helper function to check whether a number is prime
    bool isPrime(long long n) {
        if (n <= 1) return false;          // 0 and 1 are not prime
        if (n == 2) return true;           // 2 is the only even prime
        if (n % 2 == 0) return false;      // Other even numbers are not prime
        
        // Check divisibility from 3 to sqrt(n)
        for (long long i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;  // If divisible, not prime
        }
        return true; // If no divisors found, it's a prime
    }

    // Core function to compute the sum of top 3 largest unique primes from substrings
    long long sumPrimes(string s) {
        unordered_set<long long> uniquePrimes; // To store unique prime numbers only
        int n = s.size();

        // Generate all possible substrings of s
        for (int i = 0; i < n; ++i) {
            string temp = "";
            for (int j = i; j < n; ++j) {
                temp += s[j];  // Build the substring from i to j
                
                // Skip substrings with leading zeros (like "01", "001", etc.)
                if (temp.length() > 1 && temp[0] == '0') continue;

                // Convert substring to number
                long long val = stoll(temp);

                // Check if the number is prime and insert if unique
                if (isPrime(val)) {
                    uniquePrimes.insert(val);
                }
            }
        }

        // If no prime numbers found, return 0
        if (uniquePrimes.empty()) return 0;

        // Transfer primes to a vector for sorting
        vector<long long> primes(uniquePrimes.begin(), uniquePrimes.end());
        
        // Sort the primes in descending order to get the largest ones first
        sort(primes.rbegin(), primes.rend());

        // Calculate the sum of top 3 largest primes (or fewer if less than 3 exist)
        long long sum = 0;
        for (int i = 0; i < min(3, (int)primes.size()); ++i) {
            sum += primes[i];
        }

        return sum;
    }

    // Public function to be called as the solution entry point
    long long sumOfLargestPrimes(string s) {
        return sumPrimes(s);
    }
};
