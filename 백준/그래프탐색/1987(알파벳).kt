private var R: Int = 0
private var C: Int = 0
private lateinit var map: Array<CharArray>
private var answer = 0

private val dr = intArrayOf(-1, 1, 0, 0)
private val dc = intArrayOf(0, 0, -1, 1)

fun main() {
    // input
    val (r, c) = readln().split(" ").map { it.toInt() }
    R = r
    C = c

    map = Array(R) { CharArray(C) }
    for (r in 0 until R) {
        val str = readln()
        for (c in str.indices) {
            map[r][c] = str[c]
        }
    }

    // solution
    val history = mutableSetOf<Char>()
    history.add(map[0][0])
    dfs(0, 0, history)

    // output
    println(answer)
}

fun dfs(curR: Int, curC: Int, history: MutableSet<Char>) {
    if (answer < history.size) {
        answer = history.size
    }

    for (d in 0 until 4) {
        val nextR = curR + dr[d]
        val nextC = curC + dc[d]

        if ((nextR !in 0 until R) || (nextC !in 0 until C)) {
            continue
        }

        if (history.contains(map[nextR][nextC])) {
            continue
        }

        history.add(map[nextR][nextC])
        dfs(nextR, nextC, history)
        history.remove(map[nextR][nextC])
    }
}
