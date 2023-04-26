class Solution {

    lateinit var users: Array<IntArray>
    lateinit var emoticons: IntArray

    companion object {
        private val SALE_RATE = intArrayOf(10, 20, 30, 40)
        private var answer = intArrayOf(-1, -1)
    }

    fun solution(users: Array<IntArray>, emoticons: IntArray): IntArray {

        this.users = users
        this.emoticons = emoticons

        calSalePermutation(0, emoticons.size, IntArray(size = emoticons.size))

        return answer
    }

    private fun calSalePermutation(curDepth: Int, maxDepth: Int, permutation: IntArray) {
        if (maxDepth == curDepth) {
            val result = calSaleResult(permutation)
            if (result[0] > answer[0]) {
                answer = result
            } else if (result[0] == answer[0]) {
                if (result[1] > answer[1]) {
                    answer = result
                }
            }
            return
        }

        for (idx in SALE_RATE.indices) {
            permutation[curDepth] = SALE_RATE[idx]
            calSalePermutation(curDepth + 1, maxDepth, permutation)
        }
    }

    private fun calSaleResult(saleRates: IntArray): IntArray {
        var emoticonPlusMemberCnt = 0
        var totalSalePrice = 0

        for (user in users) {
            val minSaleRate = user[0]
            val maxSalePrice = user[1]
            var buyPrice = 0

            for (idx in emoticons.indices) {
                if (minSaleRate <= saleRates[idx]) {
                    buyPrice += (emoticons[idx] * (100 - saleRates[idx])) / 100
                }
            }

            if (maxSalePrice <= buyPrice) {
                emoticonPlusMemberCnt++
            } else {
                totalSalePrice += buyPrice
            }
        }

        return intArrayOf(emoticonPlusMemberCnt, totalSalePrice)
    }
}
