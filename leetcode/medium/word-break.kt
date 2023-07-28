/*
Solution 1 : BFS
Time Complexity : O(n^3 + mk) (n : length of s, m : length of wordDict, k : average length of the words in wordDict)
(Detail : BFS -> O(n^3) + Convert to HashSet -> O(mk))
Space Complexity : O(n + mk)
*/
class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        // 1. convert wordDict to HashSet
        val words = wordDict.toHashSet()

        // 2. Init queue and visited array
        val queue = ArrayDeque<Int>()
        val visited = BooleanArray(s.length) { false }

        // 4. start bfs
        queue.add(0)
        while (queue.isNotEmpty()) {
            val start = queue.removeFirst()

            if (start == s.length) {
                return true
            }

            for (end in start + 1..s.length) {
                if (!visited[end - 1] && words.contains(s.substring(start, end))) {
                    visited[end - 1] = true
                    queue.addLast(end)
                }
            }
        }

        // 5. if we can't reach last node than return false.
        return false
    }
}

/*
Solution 2 : Dynamic Programming (Bottom-Up)
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
Solution 3 : DFS + Memorization
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
