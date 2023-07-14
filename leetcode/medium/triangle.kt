// Solution 1 : DFS + Memorization
private const val INIT_VALUE = -2000001
private const val MAX_VALUE = 2000001

private var n = 0
private lateinit var memo: Array<IntArray>
private val dr = arrayOf(1, 1)
private val dc = arrayOf(0, 1)

class Solution {
    fun minimumTotal(triangle: List<List<Int>>): Int {
        n = triangle.size
        memo = Array(n) { IntArray(n) { INIT_VALUE } }
        return getMinimumTotal(0, 0, triangle)
    }

    private fun getMinimumTotal(r: Int, c: Int, triangle: List<List<Int>>): Int {
        // base case
        if (r == n - 1) {
            return triangle[r][c]
        }

        var minimumTotal = MAX_VALUE
        for (d in 0..1) {
            val nextR = r + dr[d]
            val nextC = c + dc[d]

            if (nextC in 0..nextR) {
                if (memo[nextR][nextC] == INIT_VALUE) {
                    memo[nextR][nextC] = getMinimumTotal(nextR, nextC, triangle)
                }
                minimumTotal = minOf(minimumTotal, memo[nextR][nextC])
            }
        }
        return minimumTotal + triangle[r][c]
    }
}

// Solution 2 : Dynamic Programming(Bottom-Up)
class Solution {
    fun minimumTotal(triangle: List<List<Int>>): Int {
        val n = triangle.size
        val dp = Array(n) { IntArray(n) { 0 } }
        dp[0][0] = triangle[0][0]
        for (r in 1 until n) {
            for (c in 0..r) {
                when (c) {
                    0 -> dp[r][c] = dp[r - 1][c] + triangle[r][c]
                    r -> dp[r][c] = dp[r - 1][c - 1] + triangle[r][c]
                    else -> dp[r][c] = minOf(dp[r - 1][c - 1], dp[r - 1][c]) + triangle[r][c]
                }
            }
        }

        return dp[n - 1].min()!!
    }
}

// Solution 2 - 2 : Dynamic Programming(Bottom-Up) Optimizing Space Complextiy to O(n)
class Solution {
    fun minimumTotal(triangle: List<List<Int>>): Int {
        val n = triangle.size
        val dp = triangle[n - 1].toIntArray()
        for (r in n - 2 downTo 0) {
            for (c in 0..r) {
                dp[c] = minOf(dp[c], dp[c + 1]) + triangle[r][c]
            }
        }
        return dp[0]
    }
}
