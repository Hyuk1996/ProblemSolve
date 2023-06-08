private var N = 0
private var M = 0
private lateinit var map: Array<CharArray>

private val dr = intArrayOf(-1, 1, 0, 0)
private val dc = intArrayOf(0, 0, -1, 1)

fun main() {
    // input
    val (n, m) = readln().split(" ").map { it.toInt() }
    N = n
    M = m

    var redBall = Position(-1, -1)
    var blueBall = Position(-1, -1)
    map = Array(N) { CharArray(M) }
    for (r in 0 until N) {
        val column = readln()
        for (c in 0 until M) {
            if (column[c] == 'R') {
                redBall = Position(r, c)
                map[r][c] = '.'
            } else if (column[c] == 'B') {
                blueBall = Position(r, c)
                map[r][c] = '.'
            } else {
                map[r][c] = column[c]
            }
        }
    }

    // solution
    val result = dfs(redBall, blueBall, 1)

    // output
    println("${if (result) 1 else 0}")
}

fun dfs(redBall: Position, blueBall: Position, cnt: Int): Boolean {
    if (cnt > 10) {
        return false
    }

    for (d in 0..3) {
        var curRedR = redBall.r
        var curRedC = redBall.c
        var curBlueR = blueBall.r
        var curBlueC = blueBall.c
        var isRedFinished = false
        var isBlueFinished = false

        // move redball
        while (true) {
            var nextR = curRedR + dr[d]
            var nextC = curRedC + dc[d]

            if (nextR !in 0 until N || nextC !in 0 until M) {
                break
            }

            if (map[nextR][nextC] == '#') {
                break
            }

            if (map[nextR][nextC] == 'O') {
                isRedFinished = true
                break
            }

            curRedR = nextR
            curRedC = nextC
        }

        // move blueball
        while (true) {
            var nextR = curBlueR + dr[d]
            var nextC = curBlueC + dc[d]

            if (nextR !in 0 until N || nextC !in 0 until M) {
                break
            }

            if (map[nextR][nextC] == '#') {
                break
            }

            if (map[nextR][nextC] == 'O') {
                isBlueFinished = true
                break
            }

            curBlueR = nextR
            curBlueC = nextC
        }

        if (isBlueFinished) {
            continue
        } else {
            if (isRedFinished) {
                return true
            } else {
                if (curRedR == curBlueR && curRedC == curBlueC) {
                    if (d == 0) {
                        if (redBall.r < blueBall.r) {
                            curBlueR++
                        } else {
                            curRedR++
                        }
                    } else if (d == 1) {
                        if (redBall.r > blueBall.r) {
                            curBlueR--
                        } else {
                            curRedR--
                        }
                    } else if (d == 2) {
                        if (redBall.c < blueBall.c) {
                            curBlueC++
                        } else {
                            curRedC++
                        }
                    } else {
                        if (redBall.c > blueBall.c) {
                            curBlueC--
                        } else {
                            curRedC--
                        }
                    }
                }

                if (dfs(Position(curRedR, curRedC), Position(curBlueR, curBlueC), cnt + 1)) {
                    return true
                }
            }
        }
    }
    return false
}

data class Position(val r: Int, val c: Int)
