fun main() {
    // input
    val (N, M) = readln().split(" ").map { it.toInt() }

    val map = Array(N + 1) { IntArray(M + 1) }
    for (r in 1..N) {
        val columns = readln().split(" ").map { it.toInt() }
        for (c in 1..M) {
            map[r][c] = columns[c - 1]
        }
    }

    val K = readln().toInt()
    val boundaries = Array(K) { IntArray(4) }
    for (i in 0 until K) {
        val info = readln().split(" ").map { it.toInt() }
        for (j in info.indices) {
            boundaries[i][j] = info[j]
        }
    }

    // solution
    val cache = Array(N + 1) { IntArray(M + 1) }
    for (r in 1 .. N) {
        for (c in 1 .. M) {
            cache[r][c] = cache[r - 1][c] + cache[r][c - 1] - cache[r - 1][c - 1] + map[r][c]
        }
    }

    val answers = mutableListOf<Int>()
    for (boundary in boundaries) {
        val x1 = boundary[0]
        val y1 = boundary[1]
        val x2 = boundary[2]
        val y2 = boundary[3]

        answers.add(cache[x2][y2] - cache[x1 - 1][y2] - cache[x2][y1 - 1] + cache[x1 - 1][y1 - 1])
    }

    // output
    for (answer in answers) {
        println(answer)
    }
}
