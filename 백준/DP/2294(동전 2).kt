fun main() {
    // input
    val (n, k) = readln().split(" ").map { it.toInt() }
    val coin = mutableSetOf<Int>()
    for (i in 1..n) {
        val value = readln().toInt()
        if (!coin.contains(value)) {
            coin.add(value)
        }
    }

    // solution
    val sortedCoin = coin.toList().sorted()
    val dp = IntArray(k + 1) { 10001 }
    dp[0] = 0
    for (i in 1..k) {
        for (coin in sortedCoin) {
            if (coin > i) {
                break
            }
            dp[i] = minOf(dp[i], dp[i - coin] + 1)
        }
    }

    // output
    println("${if (dp[k] == 10001) -1 else dp[k]}")
}
