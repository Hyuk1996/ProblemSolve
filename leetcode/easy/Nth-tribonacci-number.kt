// Solution1 : Dynamic Programming (top down)
class Solution {
    fun tribonacci(n: Int): Int {
        val dp = IntArray(n+1) { -1 }
        return tribonacci(n, dp)
    }

    private fun tribonacci(n: Int, dp: IntArray): Int {
        if (n == 0) {
            return 0
        }
        if (n == 1) {
            return 1
        }
        if (n == 2) {
            return 1
        }

        if (dp[n - 3] == -1) {
            dp[n - 3] = tribonacci(n - 3, dp)
        }
        if (dp[n - 2] == -1) {
            dp[n - 2] = tribonacci(n - 2, dp)
        }
        if (dp[n - 1] == -1) {
            dp[n - 1] = tribonacci(n - 1, dp)
        }

        return dp[n - 3] + dp[n - 2] + dp[n - 1]
    }
}

// Solution2 : Dynamic Programming (bottom up)
class Solution {
    fun tribonacci(n: Int): Int {
        var a = 0
        var b = 1
        var c = 1
        if (n == 0) {
            return a
        }
        if (n == 1) {
            return b
        }
        if (n == 2) {
            return c
        }
        
        var d = 0
        for (i in 3 .. n) {
            d = a + b + c
            
            a = b
            b = c
            c = d
        }
        return d
    }
}
