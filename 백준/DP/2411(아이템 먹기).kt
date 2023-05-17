fun main() {
    // input
    val (N, M, A, B) = readln().split(" ").map { it.toInt() }

    val dests = mutableListOf<Position>()
    val map = Array(N + 1) { IntArray(M + 1) { 0 } }
    for (i in 1..A) {
        val (r, c) = readln().split(" ").map { it.toInt() }
        dests.add(Position(r, c))
        map[r][c] = 1
    }
    dests.add(Position(N, M))

    for (i in 1..B) {
        val (r, c) = readln().split(" ").map { it.toInt() }
        map[r][c] = 2
    }

    // solution
    dests.sortWith(compareBy({ it.r }, { it.c }))
    val dp = Array(N + 1) { IntArray(M + 1) { 0 } }
    var startR = 1
    var startC = 1
    dp[startR][startC] = 1
    var answer = 1
    for ((destR, destC) in dests) {
        for (r in startR..destR) {
            for (c in startC..destC) {
                if (r == startR && c == startC) {
                    dp[startR][startC] = 1
                    continue
                }

                if (map[r][c] == 2) {
                    dp[r][c] = 0
                } else if (map[r - 1][c] != 2 && map[r][c - 1] != 2) {
                    dp[r][c] = dp[r - 1][c] + dp[r][c - 1]
                } else if (map[r - 1][c] != 2) {
                    dp[r][c] = dp[r - 1][c]
                } else if (map[r][c - 1] != 2) {
                    dp[r][c] = dp[r][c - 1]
                }
            }
        }
        startR = destR
        startC = destC

        answer *= dp[destR][destC]
    }

    // output
    println(answer)
}

data class Position(val r: Int, val c: Int)
