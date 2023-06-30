// Solution 1 : recursive + memorization
class Solution {
    fun rob(nums: IntArray): Int {
        val n = nums.size
        val memo = IntArray(n) { -1 }
        return maxRobbedValue(n - 1, memo, nums)
    }

    private fun maxRobbedValue(i: Int, memo: IntArray, nums: IntArray): Int {
        if (i < 0) {
            return 0
        }

        if (memo[i] >= 0) {
            return memo[i]
        }

        memo[i] = maxOf(maxRobbedValue(i - 2, memo, nums) + nums[i], maxRobbedValue(i - 1, memo, nums))
        return memo[i]
    }
}

// Solution 2 : dynamic programming (bottom up)
class Solution {
    fun rob(nums: IntArray): Int {
        var prev1 = 0
        var prev2 = 0
        var cur = 0
        for (i in nums.indices) {
            cur = maxOf(prev2 + nums[i], prev1)

            prev2 = prev1
            prev1 = cur
        }

        return cur
    }
}
