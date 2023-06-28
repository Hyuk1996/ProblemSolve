// Solution1 : bottom-up
class Solution {
    fun fib(n: Int): Int {
        if (n < 2) {
            return n
        }
        
        var a = 1
        var b = 0
        var c = 0
        for (i in 2 .. n) {
            c = a + b
            b = a
            a = c
        }
        return c
    }
}

// Solution2 : top-down
class Solution {
    fun fib(n: Int): Int {
        if (n < 2) {
            return n
        }

        val dp = IntArray(n + 1) { - 1}
        dp[0] = 0
        dp[1] = 1
        return fibonacci(n, dp)
    }

    private fun fibonacci(n: Int, dp: IntArray): Int {
        if (dp[n - 2] == -1) {
            dp[n - 2] = fibonacci(n - 2, dp)
        }
        if (dp[n - 1] == -1) {
            dp[n - 1] = fibonacci(n - 1, dp)
        }
        return dp[n - 1] + dp[n - 2]
    }
}
