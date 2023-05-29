fun main() {
    // input
    val N = readln().toInt()

    // solution
    var answer = 0
    for (cnt in 1..N) {
        if (cnt % 2 != 0) {
            if (N % cnt == 0) {
                val mid = N / cnt
                val q = cnt / 2
                if (mid - q > 0 && mid + q <= N) {
                    answer++
                } else {
                    break
                }
            }
        } else {
            val tmp = cnt / 2
            if (N % tmp == 0) {
                val mid = N / tmp
                if (mid % 2 != 0) {
                    val lo = mid / 2
                    val hi = mid / 2 + 1
                    val q = tmp - 1
                    if (lo - q > 0 && hi + q <= N) {
                        answer++
                    } else {
                        break
                    }
                }
            }
        }
    }

    // output
    println(answer)
}
