fun main() {
    // input
    var (N, K) = readln().split(" ").map { it.toInt() }
    val waters = readln().split(" ").map { it.toInt() }.toTypedArray()

    // solution
    val queue = ArrayDeque<Int>()
    val visited = mutableSetOf<Int>()

    for (water in waters) {
        queue.addLast(water)
        visited.add(water)
    }
    var answer = 0L
    var dist = 0
    while (queue.isNotEmpty() && K > 0) {
        var qSize = queue.size
        while (qSize-- > 0) {
            val first = queue.removeFirst()

            if (dist >= 1) {
                answer += dist
                K--
                if (K == 0) {
                    break
                }
            }

            if (!visited.contains(first + 1)) {
                queue.addLast(first + 1)
                visited.add(first + 1)
            }
            if (!visited.contains(first - 1)) {
                queue.addLast(first - 1)
                visited.add(first - 1)
            }
        }
        dist++
    }

    // output
    println(answer)
}
