fun main() {
    // input
    val (N, K) = readln().split(" ").map { it.toInt() }
    val arr = readln().split(" ").map { it.toInt() }.toTypedArray()

    // solution
    val map = mutableMapOf<Long, Int>()
    map[0L] = 1

    var sum = 0L
    var answer = 0L
    arr.forEach {
        sum += it
        answer += map[sum - K] ?: 0

        map[sum] = (map[sum] ?: 0) + 1
    }

    // output
    println(answer)
}
