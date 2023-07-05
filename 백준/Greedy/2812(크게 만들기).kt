fun main() {
    // input
    var (N, K) = readln().split(" ").map { it.toInt() }
    val num = readln()

    // solution
    val answer = ArrayDeque<Char>()
    for (i in 0 until N) {
        while (answer.isNotEmpty() && K > 0) {
            if (answer.last() - '0' < num[i] - '0') {
                answer.removeLast()
                --K
            } else {
                break
            }
        }
        answer.addLast(num[i])
    }

    while (K > 0) {
        answer.removeLast()
        --K
    }

    // output
    println(answer.joinToString(separator = ""))
}
