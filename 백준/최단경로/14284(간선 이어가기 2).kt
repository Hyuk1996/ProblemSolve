import java.util.PriorityQueue

private var n = 0
private var m = 0
private lateinit var graph: Array<MutableList<Pair<Int, Int>>>
private lateinit var dists: IntArray
private var s = 0
private var t = 0
private var answer = 10000001

fun main() {
    // input
    val (n_, m_) = readln().split(" ").map { it.toInt() }
    n = n_
    m = m_

    graph = Array(n + 1) { ArrayList() }
    for (i in 1 .. m) {
        val (a, b, c) = readln().split(" ").map { it.toInt() }
        graph[a].add(Pair(b, c))
        graph[b].add(Pair(a, c))
    }

    val (s_, t_) = readln().split(" ").map { it.toInt() }
    s = s_
    t = t_

    // solution
    val pq = PriorityQueue<Pair<Int, Int>>(compareBy { it.second })
    dists = IntArray(n + 1) { 10000001 }

    pq.add(Pair(s, 0))
    dists[s] = 0

    while (pq.isNotEmpty()) {
        val node = pq.poll()
        val v = node.first
        val dist = node.second

        if (dists[v] < dist) {
            continue
        }

        for (adjNode in graph[v]) {
            val u = adjNode.first
            val w = adjNode.second

            if (dists[v] + w < dists[u]) {
                dists[u] = dists[v] + w
                pq.add(Pair(u, dists[u]))
            }
        }
    }

    // output
    println(dists[t])
}
