/* 
Solution 1 : Brute Force + Two Pointer
Time Complexity : O(n^3)
Space Complexity : O(1)
*/
private var startIdx = -1
private var length = -1

class Solution {
    fun longestPalindrome(s: String): String {
        startIdx = -1
        length = -1

        for (i in s.indices) {
            searchLongestPalindromicSubstring(s, i, i)
            searchLongestPalindromicSubstring(s, i, i + 1)
        }

        return s.substring(startIdx, startIdx + length)
    }

    private fun searchLongestPalindromicSubstring(s: String, _left: Int, _right: Int) {
        var curLength = 0
        var left = _left
        var right = _right
        while (left >= 0 && right < s.length && s[left] == s[right]) {
            curLength += if (left == right) 1 else 2
            --left
            ++right
        }

        if (curLength > length) {
            startIdx = ++left
            length = curLength
        }
    }
}

/*
Solution 2 : Dynamic Programming (Bottom-Up)
Time Complexity : O(n^2)
Space Complextiy : O(n^2)
*/
class Solution {
    fun longestPalindrome(s: String): String {
        val n = s.length

        var startIdx = -1
        var endIdx = -1
        var length = -1
        val dp = Array(n) { BooleanArray(n) { false } }

        for (len in 1..n) {
            for (i in 0 until n - len + 1) {
                val j = i + len - 1

                when (len) {
                    1 -> dp[i][j] = true
                    2 -> dp[i][j] = (s[i] == s[j])
                    else -> dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1])
                }

                if (dp[i][j] && length < j - i + 1) {
                    length = j - i + 1
                    startIdx = i
                    endIdx = j
                }
            }
        }
        
        return s.substring(startIdx, endIdx + 1)
    }
}

/*
Solution 3 : Two Pointer
Time Complexity : O(n^2)
Space Complexity : O(1)
*/
private var startIdx = -1
private var length = -1

class Solution {
    fun longestPalindrome(s: String): String {
        startIdx = -1
        length = -1

        for (i in s.indices) {
            searchLongestPalindromicSubstring(s, i, i)
            searchLongestPalindromicSubstring(s, i, i + 1)
        }

        return s.substring(startIdx, startIdx + length)
    }

    private fun searchLongestPalindromicSubstring(s: String, _left: Int, _right: Int) {
        var curLength = 0
        var left = _left
        var right = _right
        while (left >= 0 && right < s.length && s[left] == s[right]) {
            curLength += if (left == right) 1 else 2
            --left
            ++right
        }

        if (curLength > length) {
            startIdx = ++left
            length = curLength
        }
    }
}
