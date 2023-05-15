import java.util.*
import kotlin.math.sqrt

fun main() {
    // input
    val scanner = Scanner(System.`in`)
    val N = scanner.nextInt()
    val M = scanner.nextInt()

    val map = Array(N) { "" }
    for (r in 0 until N) {
        map[r] = scanner.next()
    }

    // solution
    var answer = -1
    val sb = StringBuilder()
    for (dr in -(N - 1) until N) {
        for (dc in -(M - 1) until M) {
            for (r in 0 until N) {
                for (c in 0 until M) {
                    sb.clear()
                    var curR = r
                    var curC = c
                    while ((curR in 0 until N) && (curC in 0 until M)) {
                        sb.append(map[curR][curC])

                        val nextR = curR + dr
                        val nextC = curC + dc

                        if (curR == nextR && curC == nextC) {
                            break
                        }
                        curR = nextR
                        curC = nextC
                    }

                    for (len in 1..sb.length) {
                        val number = sb.substring(0, len).toInt()
                        val sqrt = sqrt(number.toDouble())
                        if (sqrt.toInt() * sqrt.toInt() == number) {
                            if (answer < number) {
                                answer = number
                            }
                        }
                    }
                }
            }
        }
    }

    // output
    println(answer)
}
