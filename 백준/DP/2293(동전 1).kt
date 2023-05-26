fun main() {
    // input
    val (n, k) = readln().split(" ").map { it.toInt() }
    val coins = IntArray(n) { 0 }
    for (i in 0 until n) {
        coins[i] = readln().toInt()
    }

    // solution
    val dp = IntArray(k + 1) { 0 }
    dp[0] = 1
    for (coin in coins) {
        for (i in coin .. k) {
            dp[i] += dp[i - coin]
        }
    }
    
    // output
    println(dp[k])
}
