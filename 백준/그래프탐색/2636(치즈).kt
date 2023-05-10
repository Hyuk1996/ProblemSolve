import java.util.*
import kotlin.collections.ArrayDeque

val dr = intArrayOf(-1, 1, 0, 0)
val dc = intArrayOf(0, 0, -1, 1)

fun main() {
    // input
    val scanner = Scanner(System.`in`)

    val N = scanner.nextInt()
    val M = scanner.nextInt()
    val map = Array<IntArray>(N) { IntArray(size = M) }
    for (r in 0 until N) {
        for (c in 0 until M) {
            map[r][c] = scanner.nextInt()
        }
    }

    // solution
    var lastRemainCheeseCnt = 0
    var hour = 0
    do {
        // count current cheese
        var curCheeseCnt = 0
        for (r in 0 until N) {
            for (c in 0 until M) {
                if (map[r][c] == 1) {
                    curCheeseCnt++
                }
            }
        }

        if (curCheeseCnt == 0) {
            break
        }

        // get air area
        val air = Array(N) { BooleanArray(M) { false } }

        val queue = ArrayDeque<Position>()
        queue.add(Position(0, 0))
        air[0][0] = true

        while (!queue.isEmpty()) {
            val pos = queue.removeFirst()
            for (d in 0 until 4) {
                val nextR = pos.r + dr[d]
                val nextC = pos.c + dc[d]

                if (nextR in 0 until N && nextC in 0 until M) {
                    if (map[nextR][nextC] == 0 && !air[nextR][nextC]) {
                        queue.addLast(Position(nextR, nextC))
                        air[nextR][nextC] = true
                    }
                }
            }
        }

        // count and check erased cheese
        var erasedCheeseCnt = 0
        for (r in 0 until N) {
            for (c in 0 until M) {
                if (map[r][c] == 1) {
                    for(d in 0 until 4) {
                        val nextR = r + dr[d]
                        val nextC = c + dc[d]

                        if (nextR in 0 until N && nextC in 0 until M) {
                            if (air[nextR][nextC]) {
                                map[r][c] = 2
                                erasedCheeseCnt++
                                break
                            }
                        }
                    }
                }
            }
        }

        if (curCheeseCnt == erasedCheeseCnt) {
            lastRemainCheeseCnt = curCheeseCnt
        }

        for (r in 0 until N) {
            for (c in 0 until M) {
                if (map[r][c] == 2) {
                    map[r][c] = 0
                }
            }
        }
        hour++
    } while (lastRemainCheeseCnt == 0)

    // output
    println(hour)
    println(lastRemainCheeseCnt)
}
