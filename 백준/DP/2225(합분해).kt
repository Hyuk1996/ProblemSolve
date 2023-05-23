private const val MOD = 1000000000

fun main() {
    // input
    val (N, K) = readln().split(" ").map { it.toInt() }

    // solution
    val dp = Array(K + 1) { IntArray(N + 1) { 0 } }

    for (n in 0 .. N) {
        dp[1][n] = 1
    }

    for (k in 2 .. K) {
        for (n in 0 .. N) {
            for (i in 0 .. n) {
                dp[k][n] = ((dp[k][n] + dp[k - 1][i]) % MOD)
            }
        }
    }
    
    // output
    println(dp[K][N])
}
