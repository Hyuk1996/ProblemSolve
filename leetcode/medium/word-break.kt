class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        // dp[i] ([i, s.length] 문자열의 wordDict 표현 가능 여부)
        val dp = BooleanArray(s.length + 1) { false }
        dp[s.length] = true

        for (i in s.length downTo 0) {
            for (word in wordDict) {
                if (i + word.length <= s.length && word == s.substring(i, i + word.length)) {
                    dp[i] = dp[i + word.length]
                }
                if (dp[i]) break
            }
        }

        println(dp.asList())

        return dp[0]
    }
}
