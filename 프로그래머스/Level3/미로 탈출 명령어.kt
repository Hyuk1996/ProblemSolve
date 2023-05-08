class Solution {
    private val path: CharArray = charArrayOf('d', 'l', 'r', 'u')
    private val dr: IntArray = intArrayOf(1, 0, 0, -1)
    private val dc: IntArray = intArrayOf(0, -1, 1, 0)

    private lateinit var visited: Array<Array<Array<Boolean>>>
    private var n: Int = 0
    private var m: Int = 0
    private var x: Int = 0
    private var y: Int = 0
    private var r: Int = 0
    private var c: Int = 0
    private var answer: String = ""

    fun solution(n: Int, m: Int, x: Int, y: Int, r: Int, c: Int, k: Int): String {

        this.visited = Array(n + 1) { Array(m + 1) { Array(k + 1) { false } } }
        this.n = n
        this.m = m
        this.x = x
        this.y = y
        this.r = r
        this.c = c

        visited[x][y][k] = true
        val log = StringBuilder()
        dfs(x, y, k, log)

        return if (answer == "") "impossible" else answer
    }

    private fun dfs(curR: Int, curC: Int, remain: Int, log: StringBuilder) {
        if (remain == 0) {
            if (curR == r && curC == c) {
                answer = log.toString()
            }
            return
        }

        for (d in 0 until 4) {
            val nextR = curR + dr[d]
            val nextC = curC + dc[d]
            val path = path[d]

            if ((nextR in 1..n) && (nextC in 1..m)) {
                if (!visited[nextR][nextC][remain - 1]) {
                    visited[nextR][nextC][remain - 1] = true
                    log.append(path)

                    dfs(nextR, nextC, remain - 1, log)
                    log.deleteCharAt(log.length - 1)
                }
            }
        }
    }
}
