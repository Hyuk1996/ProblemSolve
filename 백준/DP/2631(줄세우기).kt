import java.util.Scanner

fun main() {
    // input
    val scanner = Scanner(System.`in`)
    val N = scanner.nextInt()

    val kids = IntArray(size = N)
    for (i in 0 until N) {
        kids[i] = scanner.nextInt()
    }

    // solution
    val dp = IntArray(N) { 1 }
    for (i in 0 until N) {
        for (j in i - 1 downTo 0) {
            if (kids[i] > kids[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1
            }
        }
    }

    val LISLength = dp.maxOrNull()!!

    // output
    println(N - LISLength)
}
