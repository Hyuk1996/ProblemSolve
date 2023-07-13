// Solution 1 : DFS + Memorization
private var m = 0
private var n = 0
private lateinit var memo: Array<IntArray>
private val dr = arrayOf(1, 0)
private val dc = arrayOf(0, 1)

class Solution {
    fun uniquePathsWithObstacles(obstacleGrid: Array<IntArray>): Int {
        m = obstacleGrid.size
        n = obstacleGrid[0].size
        // memo[i][j] : unique path from i, j to m - 1, n - 1
        memo = Array(m) { IntArray(n) { -1 } }

        return if (obstacleGrid[0][0] == 1) 0 else getAnswer(0, 0, obstacleGrid)
    }

    private fun getAnswer(r: Int, c: Int, obstacleGrid: Array<IntArray>): Int {
        // base case
        if (r == m - 1 && c == n - 1) {
            return if (obstacleGrid[r][c] == 0) 1 else 0
        }

        var uniquePath = 0
        for (d in 0..1) {
            val nextR = r + dr[d]
            val nextC = c + dc[d]

            if (nextR in 0 until m && nextC in 0 until n) {
                if (obstacleGrid[nextR][nextC] == 0) {
                    if (memo[nextR][nextC] == -1) {
                        memo[nextR][nextC] = getAnswer(nextR, nextC, obstacleGrid)
                    }
                    uniquePath += memo[nextR][nextC]
                }
            }
        }
        return uniquePath
    }
}

// Solution 2 : Dynamic Programming(Bottom-Up)
class Solution {
    fun uniquePathsWithObstacles(obstacleGrid: Array<IntArray>): Int {
        val m = obstacleGrid.size
        val n = obstacleGrid[0].size
        // dp[i][j] : unique path 0, 0 to i, j
        val dp = Array(m) { IntArray(n) { 0 } }

        for (r in 0 until m) {
            for (c in 0 until n) {
                if (obstacleGrid[r][c] == 1) {
                    dp[r][c] = 0
                } else {
                    if (r == 0 && c == 0) {
                        dp[r][c] = 1
                    } else if (r == 0) {
                        dp[r][c] = dp[r][c - 1]
                    } else if (c == 0) {
                        dp[r][c] = dp[r - 1][c]
                    } else {
                        dp[r][c] = dp[r - 1][c] + dp[r][c - 1]
                    }
                }
            }
        }

        return dp[m - 1][n - 1]
    }
}

// Solution 2 - 2 : Dynamic Programming(Bottom-Up) Optimizing Space Complexity to O(n)
class Solution {
    fun uniquePathsWithObstacles(obstacleGrid: Array<IntArray>): Int {
        val m = obstacleGrid.size
        val n = obstacleGrid[0].size
        val dp = IntArray(n) { 0 }

        for (r in 0 until m) {
            for (c in 0 until n) {
                if (obstacleGrid[r][c] == 1) {
                    dp[c] = 0
                } else {
                    if (r == 0 && c == 0) {
                        dp[c] = 1
                    } else if (r == 0) {
                        dp[c] = dp[c - 1]
                    } else if (c == 0) {
                        /* no-operation */
                    } else {
                        dp[c] += dp[c - 1]
                    }
                }
            }
        }

        return dp[n - 1]
    }
}

// Solution 2 - 3 : Dynamic Programming(Bottom-Up) Optimizing Space Complexity to O(1)
class Solution {
    fun uniquePathsWithObstacles(obstacleGrid: Array<IntArray>): Int {
        val m = obstacleGrid.size
        val n = obstacleGrid[0].size

        for (r in 0 until m) {
            for (c in 0 until n) {
                if (obstacleGrid[r][c] == 1) {
                    obstacleGrid[r][c] = 0
                } else {
                    if (r == 0 && c == 0) {
                        obstacleGrid[r][c] = 1
                    } else if (r == 0) {
                        obstacleGrid[r][c] = obstacleGrid[r][c - 1]
                    } else if (c == 0) {
                        obstacleGrid[r][c] = obstacleGrid[r - 1][c]
                    } else {
                        obstacleGrid[r][c] = obstacleGrid[r - 1][c] + obstacleGrid[r][c - 1]
                    }
                }
            }
        }

        return obstacleGrid[m - 1][n - 1]
    }
}
