fun main() {
    // input
    val N = readln().toInt()
    val edges = mutableListOf<Edge>()
    for (i in 1 until N) {
        val (u, v, w) = readln().split(" ").map { it.toInt() }
        edges.add(Edge(u, v, w))
    }

    // solution
    var answer = -1L
    for (i in edges.indices) {

        val root1 = edges[i].u
        val root2 = edges[i].v

        val graph = Array(N) { ArrayList<Pair<Int, Int>>() }
        for (j in edges.indices) {
            if (j == i) {
                continue
            }

            val u = edges[j].u
            val v = edges[j].v
            val w = edges[j].w

            graph[u].add(Pair(v, w))
            graph[v].add(Pair(u, w))
        }

        val diameter1 = getTreeDiameter(graph, root1)
        val diameter2 = getTreeDiameter(graph, root2)

        answer = maxOf(answer, diameter1 + diameter2 + edges[i].w)
    }

    // output
    println(answer)
}

fun getTreeDiameter(graph: Array<ArrayList<Pair<Int, Int>>>, root: Int): Long {
    val dist = LongArray(graph.size) { -1L }
    dist[root] = 0
    dfs(graph, root, dist)

    var x = root
    var maxDist = dist[root]
    for (i in dist.indices) {
        if (dist[i] > maxDist) {
            x = i
            maxDist = dist[i]
        }
    }

    for (i in dist.indices) {
        dist[i] = -1L
    }

    dist[x] = 0
    dfs(graph, x, dist)

    var diameter = dist[x]
    for (i in dist.indices) {
        if (dist[i] > diameter) {
            diameter = dist[i]
        }
    }

    return diameter
}

fun dfs(graph: Array<java.util.ArrayList<Pair<Int, Int>>>, node: Int, dist: LongArray) {
    for (adjNode in graph[node]) {
        if (dist[adjNode.first] < 0) {
            dist[adjNode.first] = dist[node] + adjNode.second
            dfs(graph, adjNode.first, dist)
        }
    }
}

data class Edge(val u: Int, val v: Int, val w: Int)
