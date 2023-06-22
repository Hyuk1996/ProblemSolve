fun main() {
    // input
    val (X, Y) = readln().split(" ").map { it.toLong() }

    // solution
    val prevRate = (Y * 100) / X

    var lo: Long = 0
    var hi: Long = 1000000000
    while (lo + 1 < hi) {
        val mid = lo + (hi - lo) / 2
        val curRate = ((Y + mid) * 100) / (X + mid)

        if (prevRate == curRate) {
            lo = mid
        } else {
            hi = mid
        }
    }

    val answer = if (prevRate == ((Y + hi) * 100) / (X + hi)) -1 else hi.toInt()

    // output
    println(answer)
}
