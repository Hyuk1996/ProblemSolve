/*
Solution 1 : Dynamic Programming (Bottom-Up)
Time Complexity : O(nm) (n: s.length, m: wordDict.length
Space Complexity : O(n)
*/
class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        // dp[i] ([i, s.length] 문자열의 wordDict 표현 가능 여부)
        val dp = BooleanArray(s.length + 1) { false }
        dp[s.length] = true

        for (i in s.length downTo 0) {
            for (word in wordDict) {
                if (i + word.length <= s.length && word == s.substring(i, i + word.length)) {
                    dp[i] = dp[i + word.length]
                }
                if (dp[i]) break
            }
        }
        return dp[0]
    }
}

/*
Solution 2 : DFS + Memorization
Time Complexity : O(n^2) (n: s.length)
Space Complexity : O(n^2)
*/
private lateinit var memo: IntArray
private lateinit var dict: Set<String>
private var n = 0

class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        n = s.length
        dict = wordDict.toSet()
        memo = IntArray(n + 1) { -1 }

        return getAnswer(0, s)
    }

    private fun getAnswer(start: Int, s: String): Boolean {
        // base case
        if (start == n) {
            return true
        }

        for (i in 1..n - start) {
            if (dict.contains(s.substring(start, start + i))) {
                if (memo[start + i] == -1) {
                    memo[start + i] = if (getAnswer(start + i, s)) 1 else 0
                }

                if (memo[start + i] == 1) {
                    return true
                }
            }
        }
        return false
    }
}
