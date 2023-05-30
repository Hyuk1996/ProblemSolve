private const val NORMAL = 0
private const val UNKNOWN = 1
private const val IMPOSSIBLE = 2


fun main() {
    var testCase = readln().toInt()
    while (testCase-- > 0) {
        // input
        val n = readln().toInt()
        val order = readln().split(" ").map { it.toInt() }.toIntArray()
        val m = readln().toInt()
        val changes = mutableListOf<Pair<Int, Int>>()
        for (i in 1..m) {
            val (v, u) = readln().split(" ").map { it.toInt() }
            changes.add(Pair(v, u))
        }

        // solution

        // represent graph
        val graph = Array(n + 1) { BooleanArray(n + 1) { false } }
        val indegree = IntArray(n + 1) { 0 }
        for (i in order.indices) {
            for (j in i + 1 until order.size) {
                graph[order[i]][order[j]] = true
                indegree[order[j]]++
            }
        }

        for (change in changes) {
            val u = change.first
            val v = change.second

            if (graph[u][v]) {
                graph[u][v] = false
                indegree[v]--

                graph[v][u] = true
                indegree[u]++
            } else {
                graph[v][u] = false
                indegree[u]--

                graph[u][v] = true
                indegree[v]++
            }
        }

        // topological sort
        val queue = ArrayDeque<Int>()
        val finalOrder = mutableListOf<Int>()
        var result = NORMAL

        for (i in 1..n) {
            if (indegree[i] == 0) {
                queue.addLast(i)
            }
        }
        if (queue.isEmpty()) {
            result = IMPOSSIBLE
        } else if (queue.size > 1) {
            result = UNKNOWN
        }

        while (result == NORMAL) {
            val v = queue.removeFirst()
            finalOrder.add(v)

            for (i in 1..n) {
                if (graph[v][i]) {
                    graph[v][i] = false
                    indegree[i]--

                    if (indegree[i] == 0) {
                        queue.addLast(i)
                    }
                }
            }

            if (finalOrder.size == n) {
                break
            }

            if (queue.isEmpty()) {
                result = IMPOSSIBLE
            } else if (queue.size > 1) {
                result = UNKNOWN
            }
        }

        // output
        when (result) {
            NORMAL -> {
                for (v in finalOrder) {
                    print("$v ")
                }
                println()
            }
            UNKNOWN -> {
                println("?")
            }
            else -> {
                println("IMPOSSIBLE")
            }
        }
    }
}
