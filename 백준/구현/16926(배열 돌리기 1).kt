fun main() {
    // input
    val (N, M, R) = readln().split(" ").map { it.toInt() }
    val map = Array(N + 2) { IntArray(M + 2) }
    for (r in 1..N) {
        val columns = readln().split(" ").map { it.toInt() }
        for (c in 1..M) {
            map[r][c] = columns[c - 1]
        }
    }

    // solution
    val visited = Array(N + 2) { BooleanArray(M + 2) { true } }

    for (i in 1..R) {
        // init visited array
        for (r in 1 .. N) {
            for (c in 1 .. M) {
                visited[r][c] = false
            }
        }

        // rotation
        var curR = 1
        var curC = 1

        while (!visited[curR][curC]) {
            var temp = map[curR][curC]

            // down
            while (true) {
                var nextR = curR + 1
                var nextC = curC

                if (visited[nextR][nextC]) {
                    break
                }

                val temp2 = map[nextR][nextC]
                map[nextR][nextC] = temp

                visited[nextR][nextC] = true
                temp = temp2
                curR = nextR
                curC = nextC
            }

            // right
            while (true) {
                var nextR = curR
                var nextC = curC + 1

                if (visited[nextR][nextC]) {
                    break
                }

                val temp2 = map[nextR][nextC]
                map[nextR][nextC] = temp

                visited[nextR][nextC] = true
                temp = temp2
                curR = nextR
                curC = nextC
            }

            // up
            while (true) {
                var nextR = curR - 1
                var nextC = curC

                if (visited[nextR][nextC]) {
                    break
                }

                val temp2 = map[nextR][nextC]
                map[nextR][nextC] = temp

                visited[nextR][nextC] = true
                temp = temp2
                curR = nextR
                curC = nextC
            }

            // left
            while (true) {
                var nextR = curR
                var nextC = curC - 1

                if (visited[nextR][nextC]) {
                    break
                }

                val temp2 = map[nextR][nextC]
                map[nextR][nextC] = temp

                visited[nextR][nextC] = true
                temp = temp2
                curR = nextR
                curC = nextC
            }

            curR += 1
            curC += 1
        }
    }

    // output
    for (r in 1 .. N) {
        for (c in 1 .. M) {
            print("${map[r][c]} ")
        }
        println()
    }
}
