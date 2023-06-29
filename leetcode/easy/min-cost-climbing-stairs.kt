// Solution 1 : recursive + memorization
class Solution {
    fun minCostClimbingStairs(cost: IntArray): Int {
        val dp = IntArray(cost.size + 1) { -1 }
        return minCost(cost.size, dp, cost)
    }

    private fun minCost(n: Int, dp: IntArray, cost: IntArray): Int {
        if (n == 0) {
            return 0
        }
        if (n == 1) {
            return 0
        }

        if (dp[n - 1] == -1) {
            dp[n - 1] = minCost(n - 1, dp, cost)
        }
        if (dp[n - 2] == -1) {
            dp[n - 2] = minCost(n - 2, dp, cost)
        }

        return minOf(dp[n - 1] + cost[n - 1], dp[n - 2] + cost[n - 2])
    }
}

// Solution 2 : Dynamic Programming (bottom-up)
class Solution {
    fun minCostClimbingStairs(cost: IntArray): Int {
        if (cost.size < 2) {
            return 0
        }

        var a = 0
        var b = 0
        var c = 0
        for (i in 2 .. cost.size) {
            c = minOf(a + cost[i - 2], b + cost[i - 1])
            a = b
            b = c
        }

        return c
    }
}
