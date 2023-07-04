// Solution 1 : DFS
private var N = 0
private lateinit var map: Array<IntArray>
private val dr = arrayOf(0, 1, 1)
private val dc = arrayOf(1, 0, 1)
private var answer = 0

fun main() {
    // input
    N = readln().toInt()
    map = Array(N) { IntArray(N) }
    for (r in 0 until N) {
        val columns = readln().split(" ").map { it.toInt() }
        for (c in 0 until N) {
            map[r][c] = columns[c]
        }
    }

    // solution
    dfs(0, 1, 0)

    // output
    println(answer)
}

fun dfs(r: Int, c: Int, d: Int) {
    if (r == N - 1 && c == N - 1) {
        ++answer
        return
    }

    for (i in 0..2) {
        if (d == 0 && i == 1) { // 가로면 세로로 못 움직임
            continue
        }
        if (d == 1 && i == 0) { // 세로면 가로로 못 움직임
            continue
        }

        var nextR = r + dr[i]
        var nextC = c + dc[i]

        if (i != 2) {
            if (isInBound(nextR, nextC) && map[nextR][nextC] == 0) {
                dfs(nextR, nextC, i)
            }
        } else {
            if (isInBound(nextR - 1, nextC) && isInBound(nextR, nextC) && isInBound(nextR, nextC - 1)) {
                if (map[nextR - 1][nextC] == 0 && map[nextR][nextC] == 0 && map[nextR][nextC - 1] == 0) {
                    dfs(nextR, nextC, i)
                }
            }
        }
    }
}

fun isInBound(r: Int, c: Int): Boolean {
    return (r in 0 until N) && (c in 0 until N)
}

// Solution 2 : DFS + memorization (Dynamic Programming Top Down)
private var N = 0
private lateinit var map: Array<IntArray>
private lateinit var memo: Array<Array<IntArray>>
private val dr = arrayOf(0, 1, 1)
private val dc = arrayOf(1, 0, 1)

fun main() {
    // input
    N = readln().toInt()
    map = Array(N) { IntArray(N) }
    for (r in 0 until N) {
        val columns = readln().split(" ").map { it.toInt() }
        for (c in 0 until N) {
            map[r][c] = columns[c]
        }
    }

    // solution
    memo = Array(N) { Array(N) { IntArray(3) { -1 } } }
    val answer = dfs(0, 1, 0)

    // output
    println(answer)
}

fun dfs(r: Int, c: Int, d: Int): Int {
    // base case
    if (r == N - 1 && c == N - 1) {
        return 1
    }

    memo[r][c][d] = 0

    for (i in 0..2) {
        if (d == 0 && i == 1) { // 가로면 세로로 못 움직임
            continue
        }
        if (d == 1 && i == 0) { // 세로면 가로로 못 움직임
            continue
        }

        var nextR = r + dr[i]
        var nextC = c + dc[i]

        if (i != 2) {
            if (isInBound(nextR, nextC) && map[nextR][nextC] == 0) {
                if (memo[nextR][nextC][i] == -1) {
                    memo[r][c][d] += dfs(nextR, nextC, i)
                } else {
                    memo[r][c][d] += memo[nextR][nextC][i]
                }
            }
        } else {
            if (isInBound(nextR - 1, nextC) && isInBound(nextR, nextC) && isInBound(nextR, nextC - 1)) {
                if (map[nextR - 1][nextC] == 0 && map[nextR][nextC] == 0 && map[nextR][nextC - 1] == 0) {
                    if (memo[nextR][nextC][i] == -1) {
                        memo[r][c][d] += dfs(nextR, nextC, i)
                    } else {
                        memo[r][c][d] += memo[nextR][nextC][i]
                    }
                }
            }
        }
    }
    return memo[r][c][d]
}

fun isInBound(r: Int, c: Int): Boolean {
    return (r in 0 until N) && (c in 0 until N)
}
