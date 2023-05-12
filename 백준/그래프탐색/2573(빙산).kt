import java.util.*

var map: Array<IntArray> = Array(1) { IntArray(1) }
var N: Int = 0
var M: Int = 0
val dr = intArrayOf(-1, 1, 0, 0)
val dc = intArrayOf(0, 0, -1, 1)

fun main() {
    // input
    val scanner = Scanner(System.`in`)

    N = scanner.nextInt()
    M = scanner.nextInt()

    map = Array(N) { IntArray(M) { 0 } }
    for (r in 0 until N) {
        for (c in 0 until M) {
            map[r][c] = scanner.nextInt()
        }
    }

    // solution
    var year = 0
    while (true) {

        // check ice area
        var iceAreaCnt = 0
        val visited = Array(N) { BooleanArray(M) { false } }
        for (r in 0 until N) {
            for (c in 0 until M) {
                if (map[r][c] != 0 && !visited[r][c]) {
                    iceAreaCnt++
                    dfs(r, c, visited)
                }
            }
        }

        // check separate
        if (iceAreaCnt == 0) {
            year = 0
            break
        } else if (iceAreaCnt > 1) {
            break
        }

        // ice melt
        year++
        val meltingMap = Array(N) { IntArray(M) { 0 } }
        for (r in 0 until N) {
            for (c in 0 until M) {
                if (map[r][c] != 0) {
                    for (d in 0 until 4) {
                        val nextR = r + dr[d]
                        val nextC = c + dc[d]

                        if (nextR in 0 until N && nextC in 0 until M) {
                            if (map[nextR][nextC] == 0) {
                                meltingMap[r][c]++
                            }
                        }
                    }
                }
            }
        }

        for (r in 0 until N) {
            for (c in 0 until M) {
                map[r][c] -= meltingMap[r][c]
                if (map[r][c] < 0) {
                    map[r][c] = 0
                }
            }
        }
    }

    // output
    println(year)
}

fun dfs(r: Int, c: Int, visited: Array<BooleanArray>) {
    visited[r][c] = true

    for (d in 0 until 4) {
        val nextR = r + dr[d]
        val nextC = c + dc[d]

        if (nextR in 0 until N && nextC in 0 until M) {
            if (map[nextR][nextC] != 0 && !visited[nextR][nextC]) {
                dfs(nextR, nextC, visited)
            }
        }
    }
}
