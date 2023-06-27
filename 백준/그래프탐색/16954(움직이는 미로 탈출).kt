fun main() {
    // input
    val map = Array(8) { CharArray(8) { ' ' } }
    for (r in 0..7) {
        val columns = readln()
        for (c in 0..7) {
            map[r][c] = columns[c]
        }
    }

    // solution
    val dr = arrayListOf(-1, 0, 1, -1, 0, 1, -1, 0, 1)
    val dc = arrayListOf(-1, -1, -1, 0, 0, 0, 1, 1, 1)

    val queue = ArrayDeque<Pair<Int, Int>>()
    queue.addLast(Pair(7, 0))

    var possible = false

    while (queue.isNotEmpty() && !possible) {
        val qSize = queue.size
        val visited = Array(8) { BooleanArray(8) { false } }
        for (i in 0 until qSize) {
            val (curR, curC) = queue.removeFirst()

            if (map[curR][curC] == '#') {
                continue
            }

            if (curR == 0 && curC == 7) {
                possible = true
                break
            }

            for (d in 0 until 9) {
                val nextR = curR + dr[d]
                val nextC = curC + dc[d]

                if (nextR !in 0 until 8 || nextC !in 0 until 8) {
                    continue
                }

                if (map[nextR][nextC] == '#') {
                    continue
                }

                if (visited[nextR][nextC]) {
                    continue
                }

                visited[nextR][nextC] = true
                queue.addLast(Pair(nextR, nextC))
            }
        }

        for (r in 7 downTo 0) {
            for (c in 0..7) {
                if (r == 7) {
                    if (map[r][c] == '#') {
                        map[r][c] = '.'
                    }
                } else {
                    if (map[r][c] == '#') {
                        map[r + 1][c] = '#'
                        map[r][c] = '.'
                    }
                }
            }
        }
    }

    // output
    println("${if (possible) 1 else 0}")
}
