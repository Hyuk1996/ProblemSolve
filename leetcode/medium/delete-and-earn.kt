// Solution 1 : DFS + memorization (Dynamic Programming : Top-Down)
private lateinit var buckets: IntArray
private lateinit var dp: IntArray

class Solution {
    fun deleteAndEarn(nums: IntArray): Int {

        buckets = IntArray(10001) { 0 }
        dp = IntArray(10001) { -1 }

        for (num in nums) {
            buckets[num] += num
        }

        return getAnswer(10000)
    }

    private fun getAnswer(i: Int): Int {
        // base case
        if (i < 2) {
            return buckets[i]
        }

        if (dp[i - 1] == -1) {
            dp[i - 1] = getAnswer(i - 1)
        }
        if (dp[i - 2] == -1) {
            dp[i - 2] = getAnswer(i - 2)
        }

        return maxOf(buckets[i] + dp[i - 2], dp[i - 1])
    }
}

// Solution 2 : Dynamic Programming Bottom-Uo
class Solution {
    fun deleteAndEarn(nums: IntArray): Int {
        val buckets = IntArray(10001) { 0 }
        for (num in nums) {
            buckets[num] += num
        }

        val dp = IntArray(10001) { -1 }
        dp[0] = buckets[0]
        dp[1] = buckets[1]
        for (i in 2 .. 10000) {
            dp[i] = maxOf(buckets[i] + dp[i - 2], dp[i - 1])
        }

        return dp[10000]
    }
}

// Solution 3 : Dynamic Programming Bottom-Up with Space Optimizing
class Solution {
    fun deleteAndEarn(nums: IntArray): Int {
        val buckets = IntArray(10001) { 0 }
        for (num in nums) {
            buckets[num] += num
        }
        
        var prev1 = buckets[0]
        var prev2 = buckets[1]
        var cur = 0
        for (i in 2 .. 10000) {
            cur = maxOf(buckets[i] + prev1, prev2)
            prev1 = prev2
            prev2 = cur
        }

        return cur
    }
}
