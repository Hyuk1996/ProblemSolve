import java.util.Scanner

fun main() {
    // input
    val scanner = Scanner(System.`in`)
    val N = scanner.nextInt()

    // solution
    val dp = LongArray(1000001) { -1 }
    var answer: Long = 0

    if (N in 0..10) {
        answer = N.toLong()
    } else {
        val queue = ArrayDeque<Long>()
        for (i in 1..9) {
            dp[i] = i.toLong()
            queue.addLast(i.toLong())
        }

        var idx = 10
        while (idx <= N && !queue.isEmpty()) {
            val num = queue.removeFirst()
            var lastNo = num % 10
            for (i in 0 until lastNo) {
                dp[idx++] = num * 10 + i
                queue.addLast(num * 10 + i)
            }
        }
        answer = dp[N]
    }

    // output
    println(answer)
}
