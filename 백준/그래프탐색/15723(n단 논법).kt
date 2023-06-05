import kotlin.math.asin

private var N = 0
private lateinit var graph: MutableMap<Char, MutableList<Char>>

fun main() {
    // input
    N = readln().toInt()
    graph = mutableMapOf()
    for (i in 1..N) {
        val (v, _, u) = readln().split(" ")
        if (graph.contains(v[0])) {
            graph[v[0]]?.add(u[0])
        } else {
            graph[v[0]] = mutableListOf(u[0])
        }
    }

    // solution
    val M = readln().toInt()
    val answers = mutableListOf<Char>()
    for (i in 1 .. M) {
        val (v, _, u) = readln().split(" ")
        if (dfs(v[0], u[0])) {
            answers.add('T')
        } else {
            answers.add('F')
        }
    }

    // output
    for (answer in answers) {
        println(answer)
    }
}

fun dfs(cur: Char, dest: Char): Boolean {
    if (cur == dest) {
        return true
    }

    if (graph[cur].isNullOrEmpty()) {
        return false
    }

    for (v in graph[cur]!!) {
        if (dfs(v, dest)) {
            return true
        }
    }
    return false
}
