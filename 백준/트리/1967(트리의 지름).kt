private var n = 0
private lateinit var graph: Array<MutableList<Node>>
private lateinit var visited: Array<BooleanArray>
private lateinit var dist: IntArray

fun main() {
    // input
    n = readln().toInt()
    graph = Array(n + 1) { ArrayList() }
    for (i in 1 until n) {
        val (v, u, w) = readln().split(" ").map { it.toInt() }
        graph[v].add(Node(u, w))
        graph[u].add(Node(v, w))
    }

    // solution
    visited = Array(n + 1) { BooleanArray(n + 1) { false } }
    dist = IntArray(n + 1) { 0 }
    dfs(1, 0)

    var x = 1
    var maxDist = dist[1]
    for (idx in 2..n) {
        if (dist[idx] > maxDist) {
            x = idx
            maxDist = dist[idx]
        }
    }

    visited = Array(n + 1) { BooleanArray(n + 1) { false } }
    dist = IntArray(n + 1) { 0 }
    dfs(x, 0)

    // output
    println(dist.max())
}

fun dfs(v: Int, weight: Int) {
    for (adjNode in graph[v]) {
        val u = adjNode.vertex
        val w = adjNode.weight
        if (!visited[v][u]) {
            visited[v][u] = true
            visited[u][v] = true
            dist[u] = weight + w
            dfs(u, weight + w)
        }
    }
}

data class Node(val vertex: Int, val weight: Int)
