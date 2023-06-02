import java.util.PriorityQueue

fun main() {
    // input
    val (N, M, X, Y) = readln().split(" ").map { it.toInt() }
    val graph = Array<MutableList<Pair<Int, Int>>>(N) { ArrayList() }
    for (i in 1..M) {
        val (v, u, w) = readln().split(" ").map { it.toInt() }
        graph[v].add(Pair(u, w))
        graph[u].add(Pair(v, w))
    }

    // solution

    // get shortest dist
    val dists = IntArray(N) { 10000001 }
    val pq = PriorityQueue<Pair<Int, Int>>(compareBy { it.second })

    dists[Y] = 0
    pq.add(Pair(Y, 0))
    while (pq.isNotEmpty()) {
        val (v, dist) = pq.poll()

        if (dists[v] < dist) {
            continue
        }

        for (adjV in graph[v]) {
            val u = adjV.first
            val w = adjV.second
            if (dists[u] > dists[v] + w) {
                dists[u] = dists[v] + w
                pq.add(Pair(u, dists[u]))
            }
        }
    }

    // calculate day
    dists.sort()
    var deliveryDay = 1
    var idx = 0
    while (true) {
        var remainDist = X
        if (dists[idx] * 2 > remainDist) {
            deliveryDay = -1
            break
        }

        while (idx < dists.size && dists[idx] * 2 <= remainDist) {
            remainDist -= dists[idx] * 2
            ++idx
        }

        if (idx >= dists.size) {
            break
        }

        ++deliveryDay
    }

    // output
    println(deliveryDay)
}
