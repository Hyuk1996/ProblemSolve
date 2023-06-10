fun main() {
    // input
    val (W, H) = readln().split(" ").map { it.toInt() }

    val map = Array(H) { CharArray(W) }
    val lazers = mutableListOf<Position>()
    for (r in 0 until H) {
        val info = readln()
        for (c in 0 until W) {
            if (info[c] == 'C') {
                lazers.add(Position(r, c))
            }
            map[r][c] = info[c]
        }
    }

    // solution

    // init value
    val dr = intArrayOf(-1, 1, 0, 0)
    val dc = intArrayOf(0, 0, -1, 1)
    val queue = ArrayDeque<Info>()
    val mirrorCnts = Array(H) { Array(W) { IntArray(4) { W * H + 1 } } }

    // start bfs
    val start = lazers[0]
    for (d in 0 .. 3) {
        mirrorCnts[start.r][start.c][d] = 0
    }
    queue.add(Info(Position(start.r, start.c), -1, 0))
    while (queue.isNotEmpty()) {
        val (pos, dir, cnt) = queue.removeFirst()

        if (dir != -1 && cnt > mirrorCnts[pos.r][pos.c][dir]) {
            continue
        }

        for (d in 0..3) {
            val nextR = pos.r + dr[d]
            val nextC = pos.c + dc[d]

            if (nextR !in 0 until H || nextC !in 0 until W) {
                continue
            }
            if (map[nextR][nextC] == '*') {
                continue
            }

            var mirrorCnt = cnt
            if (dir != -1 && d != dir) {
                mirrorCnt++
            }

            if (mirrorCnts[nextR][nextC][d] > mirrorCnt) {
                mirrorCnts[nextR][nextC][d] = mirrorCnt
                queue.addLast(Info(Position(nextR, nextC), d, mirrorCnt))
            }
        }
    }

    var answer = H * W + 1
    for (d in 0 .. 3) {
        answer = minOf(answer, mirrorCnts[lazers[1].r][lazers[1].c][d])
    }

    // output
    println(answer)
}

data class Position(val r: Int, val c: Int)

data class Info(val pos: Position, val dir: Int, val cnt: Int)
