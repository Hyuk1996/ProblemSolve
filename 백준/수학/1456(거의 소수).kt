import java.util.*
import kotlin.math.pow
import kotlin.math.sqrt

fun main() {
    // input
    val scanner = Scanner(System.`in`)
    val A = scanner.nextLong()
    val B = scanner.nextLong()

    // solution
    val rootB = sqrt(B.toDouble()).toInt()
    val isPrime = BooleanArray(rootB + 1) { true }
    for (i in 2 .. rootB) {
        if (!isPrime[i]) {
            continue
        }

        for (j in 2 * i .. rootB step i) {
            isPrime[j] = false
        }
    }

    val primes = mutableListOf<Int>()
    for (i in 2 .. rootB) {
        if (isPrime[i]) {
            primes.add(i)
        }
    }

    var answer = 0
    for (prime in primes) {
        var e = 2
        var p: Long = prime.toDouble().pow(e.toDouble()).toLong()
        while (p < A) {
            e++
            p = prime.toDouble().pow(e.toDouble()).toLong()
        }

        while (p <= B) {
            answer++

            e++
            p = prime.toDouble().pow(e.toDouble()).toLong()
        }
    }

    // output
    println(answer)
}
