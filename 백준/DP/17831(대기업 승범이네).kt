private lateinit var graph: Array<MutableList<Int>>
private lateinit var skillMap: MutableMap<Int, Int>
private lateinit var dp: Array<IntArray>

fun main() {
    // input
    val N = readln().toInt()
    val parents = readln().split(" ").map { it.toInt() }
    val skills = readln().split(" ").map { it.toInt() }

    // solution
    graph = Array(N + 1) { ArrayList() }
    for (i in parents.indices) {
        val child = i + 2
        val parent = parents[i]

        graph[parent].add(child)
    }

    skillMap = mutableMapOf()
    for (i in skills.indices) {
        val key = i + 1
        val skill = skills[i]

        skillMap[key] = skill
    }

    dp = Array(N + 1) { IntArray(2) { -1 } }
    maxSynergy(1)

    // output
    println("${maxOf(dp[1][0], dp[1][1])}")
}

fun maxSynergy(n: Int) {
    dp[n][0] = 0
    for (v in graph[n]) {
        if (dp[v][0] == -1) {
            maxSynergy(v)
        }
        dp[n][0] += maxOf(dp[v][0], dp[v][1])
    }

    dp[n][1] = 0
    for (v in graph[n]) {
        dp[n][1] = maxOf(
            dp[n][1],
            skillMap[n]!! * skillMap[v]!! + dp[v][0] + (dp[n][0] - maxOf(dp[v][0], dp[v][1]))
        )
    }
}
