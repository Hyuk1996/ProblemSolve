import kotlin.math.min
import kotlin.math.sqrt

fun main() {
    // input
    val (GCD, LCM) = readln().split(" ").map { it.toInt() }

    // solution
    val temp = LCM / GCD

    var a = 1
    var b = temp / a
    var minSum = a + b
    for (d in 2 .. sqrt(temp.toDouble()).toInt()) {
        if (temp % d == 0) {

            val tempA = d
            val tempB = temp / d

            // check disjoint          
            var isPossible = true
            for (i in 2 .. sqrt(tempA.toDouble()).toInt()) {
                if (tempA % i == 0) {
                    if (tempB % i == 0 || tempB % (tempA / i) == 0) {
                        isPossible = false
                        break
                    }
                }
            }

            if (isPossible) {
                if (tempA + tempB < minSum) {
                    a = tempA
                    b = tempB
                    minSum = tempA + tempB
                }
            }
        }
    }

    // output
    println("${a * GCD} ${b * GCD}")
}
