// Solution 1 : DFS + Memorization
private const val MAX = 80001

private lateinit var memo: Array<IntArray>
private var m = 0
private var n = 0
private val dr = arrayOf(1, 0)
private val dc = arrayOf(0, 1)

class Solution {
    fun minPathSum(grid: Array<IntArray>): Int {
        m = grid.size
        n = grid[0].size
        memo = Array(m) { IntArray(n) { -1 } }
        return getMinPathSum(0, 0, grid)
    }

    private fun getMinPathSum(r: Int, c: Int, grid: Array<IntArray>): Int {
        // base case
        if (r == m - 1 && c == n - 1) {
            return grid[r][c]
        }

        var minPathSum = MAX

        for (d in 0..1) {
            val nextR = r + dr[d]
            val nextC = c + dc[d]

            if (nextR in 0 until m && nextC in 0 until n) {
                if (memo[nextR][nextC] == -1) {
                    memo[nextR][nextC] = getMinPathSum(nextR, nextC, grid)
                }
                minPathSum = minOf(minPathSum, memo[nextR][nextC])
            }
        }
        return minPathSum + grid[r][c]
    }
}

// Solution 2 - 1: Dynamic Programming(Bottom-Up)
class Solution {
    fun minPathSum(grid: Array<IntArray>): Int {
        val m = grid.size
        val n = grid[0].size
        val dp = Array(m) { IntArray(n) { -1 } }
        for (r in 0 until m) {
            for (c in 0 until n) {
                if (r == 0 && c == 0) {
                    dp[r][c] = grid[r][c]
                } else if (r == 0) {
                    dp[r][c] = grid[r][c] + dp[r][c - 1]
                } else if (c == 0) {
                    dp[r][c] = grid[r][c] + dp[r - 1][c]
                } else {
                    dp[r][c] = grid[r][c] + minOf(dp[r - 1][c], dp[r][c - 1])
                }
            }
        }
        return dp[m - 1][n - 1]
    }
}

// Solution 2 - 2 : Dynamic Programming(Bottom-Up) Optimizing Space Complextiy
class Solution {
    fun minPathSum(grid: Array<IntArray>): Int {
        val m = grid.size
        val n = grid[0].size
        val dp = IntArray(n) { 0 }
        for (r in 0 until m) {
            for (c in 0 until n) {
                if (r == 0 && c == 0) {
                    dp[c] = grid[r][c]
                } else if (r == 0) {
                    dp[c] = grid[r][c] + dp[c - 1]
                } else if (c == 0) {
                    dp[c] += grid[r][c]
                } else {
                    dp[c] = grid[r][c] + minOf(dp[c], dp[c - 1])
                }
            }
        }
        return dp[n - 1]
    }
}
