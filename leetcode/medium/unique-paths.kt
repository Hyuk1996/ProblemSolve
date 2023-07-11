// Solution 1 : DFS & Memorization
private lateinit var memo: Array<IntArray>
private var M = 0
private var N = 0
private val dr = arrayOf(1, 0)
private val dc = arrayOf(0, 1)

class Solution {
    fun uniquePaths(m: Int, n: Int): Int {
        M = m
        N = n
        memo = Array(m) { IntArray(n) { -1 } }
        memo[m - 1][n - 1] = 1
        return dfs(0, 0)
    }

    private fun dfs(r: Int, c: Int): Int {
        // base case
        if (r == M - 1 && c == N - 1) {
            return 1
        }

        var pathCount = 0

        for (d in 0..1) {
            val nextR = r + dr[d]
            val nextC = c + dc[d]

            if (nextR in 0 until M && nextC in 0 until N) {
                if (memo[nextR][nextC] == -1) {
                    memo[nextR][nextC] = dfs(nextR, nextC)
                }
                pathCount += memo[nextR][nextC]
            }
        }

        return pathCount
    }
}

// Solution 2 - 1 : Dynamic Programming(Bottom-Up)
class Solution {
    fun uniquePaths(m: Int, n: Int): Int {
        val dp = Array(m) { IntArray(n) { 0 } }
        dp[0][0] = 1
        for (r in 0 until m) {
            for (c in 0 until n) {
                if (c > 0) {
                    dp[r][c] += dp[r][c - 1]
                }
                if (r > 0) {
                    dp[r][c] += dp[r - 1][c]
                }
            }
        }
        return dp[m - 1][n - 1]
    }
}

// Solution 2 - 2 : Dynamic Programming(Bottom-Up) Optimizing Space Complexity
class Solution {
    fun uniquePaths(m: Int, n: Int): Int {
        val dp = IntArray(n) { 1 }
        for (r in 1 until m) {
            for (c in 1 until n) {
                dp[c] += dp[c - 1]
            }
        }
        return dp[n - 1]
    }
}
