import java.util.*

fun main() {
    // input
    val scanner = Scanner(System.`in`)

    val N = scanner.nextInt()
    val requests = IntArray(N)
    for (i in 0 until N) {
        requests[i] = scanner.nextInt()
    }
    val M = scanner.nextInt()

    // solution
    var left = 1
    var right = requests.maxOrNull()!!
    while (right - left > 1) {
        val mid = (right - left) / 2 + left

        if (possible(mid, requests, M)) {
            left = mid
        } else {
            right = mid
        }
    }

    // output
    if (possible(right, requests, M)) {
        print(right)
    } else {
        print(left)
    }
}

fun possible(limit: Int, requests: IntArray, total: Int): Boolean {
    var calBudget = 0
    for (request in requests) {
        calBudget += if (request > limit) {
            limit
        } else {
            request
        }
    }

    return total >= calBudget
}
