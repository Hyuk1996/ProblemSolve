class Solution {
    fun countBits(n: Int): IntArray {
        val ans = IntArray(n + 1)
        for (num in 0 .. n) {
            var numberOfOne = 0
            
            var numCopy = num
            while (numCopy != 0) {
                if (numCopy % 2 == 1) {
                    numberOfOne++
                }
                numCopy /= 2
            }
            
            ans[num] = numberOfOne
        }
        return ans
    }
}
