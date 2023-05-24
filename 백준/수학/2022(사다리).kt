import kotlin.math.max
import kotlin.math.pow
import kotlin.math.sqrt

fun main() {
    // input
    val (x, y, c) = readln().split(" ").map { it.toDouble() }

    // solution
    var left = 0.0
    var right = max(x, y)
    var answer = -1.0
    while (left + 0.000001 < right) {
        val expectedW = left + (right - left) / 2.0
        val h1 = sqrt(x.pow(2) - expectedW.pow(2))
        val h2 = sqrt(y.pow(2) - expectedW.pow(2))
        val expectedC = (h1 * h2) / (h1 + h2)

        if (expectedC >= c) {
            left = expectedW
            answer = expectedW
        } else {
            right = expectedW
        }
    }

    // output
    println(String.format("%.3f", answer))
}
