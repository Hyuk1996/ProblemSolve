fun main() {
    // input
    val (N, K) = readln().split(" ").map { it.toInt() }
    val scores = readln().split(" ").map { it.toInt() }.toIntArray()

    // solution
    var left = 1
    var right = N * 20 + 1
    while (left + 1 < right) {
        var mid = left + (right - left) / 2

        // count possible group
        var totalScore = 0
        var currentGroupCnt = 0
        for (score in scores) {
            totalScore += score
            if (totalScore >= mid) {
                currentGroupCnt++
                totalScore = 0
            }
        }
        if (totalScore >= mid) {
            currentGroupCnt++
        }

        if (currentGroupCnt >= K) {
            left = mid
        } else {
            right = mid
        }
    }

    // output
    println(left)
}
