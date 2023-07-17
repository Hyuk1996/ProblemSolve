// Solution 1 : DFS + Memorization
private lateinit var memo: Array<IntArray>
private val dc = arrayOf(-1, 0, 1)
private var n = 0

private const val INIT_VALUE = 10001

class Solution {
    fun minFallingPathSum(matrix: Array<IntArray>): Int {
        n = matrix.size
        memo = Array(n) { IntArray(n) { INIT_VALUE } }

        var answer = INIT_VALUE
        for (c in 0 until n) {
            answer = minOf(answer, getMinFallingPathSum(0, c, matrix))
        }

        return answer
    }

    private fun getMinFallingPathSum(r: Int, c: Int, matrix: Array<IntArray>): Int {
        // base case
        if (r == n - 1) {
            return matrix[r][c]
        }

        var fallingPathSum = INIT_VALUE

        for (d in 0..2) {
            val nextR = r + 1
            val nextC = c + dc[d]

            if (nextC in 0 until n) {
                if (memo[nextR][nextC] == 10001) {
                    memo[nextR][nextC] = getMinFallingPathSum(nextR, nextC, matrix)
                }
                fallingPathSum = minOf(fallingPathSum, memo[nextR][nextC])
            }
        }
        return fallingPathSum + matrix[r][c]
    }
}

// Solution 2 : Dynamic Programming(Bottom-Up)
class Solution {
    fun minFallingPathSum(matrix: Array<IntArray>): Int {
        val n = matrix.size
        val dp = Array(n) { IntArray(n) }

        for (c in 0 until n) {
            dp[0][c] = matrix[0][c]
        }

        for (r in 1 until n) {
            for (c in 0 until n) {
                var preMinFallingPathSum = dp[r - 1][c]
                if (c - 1 >= 0) {
                    preMinFallingPathSum = minOf(preMinFallingPathSum, dp[r - 1][c - 1])
                }
                if (c + 1 <= n - 1) {
                    preMinFallingPathSum = minOf(preMinFallingPathSum, dp[r - 1][c + 1])
                }
                dp[r][c] = matrix[r][c] + preMinFallingPathSum
            }
        }

        var answer = dp[n - 1][0]
        for (c in 1 until n) {
            answer = minOf(answer, dp[n - 1][c])
        }

        return answer
    }
}

// Solution 2 - 2 : Dynamic Programming(Bottom-up) Optimizing Space Complexity to O(1)
class Solution {
    fun minFallingPathSum(matrix: Array<IntArray>): Int {
        val n = matrix.size

        for (r in 1 until n) {
            for (c in 0 until n) {
                var preMinFallingPathSum = matrix[r - 1][c]
                if (c - 1 >= 0) {
                    preMinFallingPathSum = minOf(preMinFallingPathSum, matrix[r - 1][c - 1])
                }
                if (c + 1 <= n - 1) {
                    preMinFallingPathSum = minOf(preMinFallingPathSum, matrix[r - 1][c + 1])
                }
                matrix[r][c] += preMinFallingPathSum
            }
        }

        return matrix[n - 1].min()!!
    }
}
