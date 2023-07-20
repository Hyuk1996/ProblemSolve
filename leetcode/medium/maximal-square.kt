/*
Solution 1 : Dynamic Programming using cumulative sum
Time Complexity : O((m^2)n)
Space Complexity : O(mn)
*/
class Solution {
    fun maximalSquare(matrix: Array<CharArray>): Int {
        // get cumulative sum
        val m = matrix.size
        val n = matrix[0].size

        val sum = Array(m) { IntArray(n) { 0 } }
        sum[0][0] += (matrix[0][0] - '0')
        for (r in 1 until m) {
            sum[r][0] = sum[r - 1][0] + (matrix[r][0] - '0')
        }
        for (c in 1 until n) {
            sum[0][c] = sum[0][c - 1] + (matrix[0][c] - '0')
        }
        for (r in 1 until m) {
            for (c in 1 until n) {
                sum[r][c] = sum[r - 1][c] + sum[r][c - 1] - sum[r - 1][c - 1] + (matrix[r][c] - '0')
            }
        }

        // get max square
        var answer = 0
        for (size in 1..m) {
            for (r in (size - 1) until m) {
                for (c in (size - 1) until n) {
                    var square = sum[r][c]
                    if (c - size >= 0) {
                        square -= sum[r][c - size]
                    }
                    if (r - size >= 0) {
                        square -= sum[r - size][c]
                    }
                    if (c - size >= 0 && r - size >= 0) {
                        square += sum[r - size][c - size]
                    }

                    if (square == (size * size)) {
                        answer = size
                        break
                    }
                }
                if (answer == size) {
                    break
                }
            }

            if (answer < size) {
                break
            }
        }

        return answer * answer
    }
}

/*
Solution 2 : Dynamic Programming using combo size
Time Complexity : O(mn)
Space Complexity : O(mn)
*/
class Solution {
    fun maximalSquare(matrix: Array<CharArray>): Int {
        val m = matrix.size
        val n = matrix[0].size
        val dp = Array(m + 1) { IntArray(n + 1) { 0 } }
        var maxCombo = 0
        for (r in 0 until m) {
            for (c in 0 until n) {
                if (matrix[r][c] == '1') {
                    dp[r + 1][c + 1] = minOf(minOf(dp[r][c + 1], dp[r + 1][c]), dp[r][c]) + 1
                    maxCombo = maxOf(maxCombo, dp[r + 1][c + 1])
                }
            }
        }

        return maxCombo * maxCombo
    }
}

/*
Solution 2 - 2 : Optimizing Space Complexity
Time Complexity : equal
Space Complexity : O(n)
*/
class Solution {
    fun maximalSquare(matrix: Array<CharArray>): Int {
        val m = matrix.size
        val n = matrix[0].size
        
        val dp = IntArray(n) { 0 }
        var prev = 0
        var maxSize = 0
        for (r in 0 until m) {
            for (c in 0 until n) {
                val temp = dp[c]
                if (r == 0 || c == 0 || matrix[r][c] == '0') {
                    dp[c] = matrix[r][c] - '0'
                } else {
                    dp[c] = minOf(prev, minOf(dp[c - 1], dp[c])) + 1
                }
                
                prev = temp
                maxSize = maxOf(maxSize, dp[c])
            }
        }

        return maxSize * maxSize
    }
}
