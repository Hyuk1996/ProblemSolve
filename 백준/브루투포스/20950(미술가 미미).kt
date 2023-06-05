import kotlin.math.abs
import kotlin.math.max

private var N = 0
private lateinit var colors: MutableList<Color>
private lateinit var goalColor: Color
private var answer = 255 + 255 + 255 + 1

fun main() {
    // input
    N = readln().toInt()
    colors = mutableListOf()
    for (i in 1..N) {
        val (r, g, b) = readln().split(" ").map { it.toInt() }
        colors.add(Color(r, g, b))
    }
    val (r, g, b) = readln().split(" ").map { it.toInt() }
    goalColor = Color(r, g, b)

    // solution
    val maxDepth = minOf(7, N)
    for (depth in 2..maxDepth) {
        combi(0, mutableListOf(), depth)
    }

    // output
    println(answer)
}

fun combi(idx: Int, curCombi: MutableList<Color>, maxDepth: Int) {
    if (maxDepth == curCombi.size) {
        var resultR = 0
        var resultG = 0
        var resultB = 0
        for (color in curCombi) {
            resultR += color.R
            resultG += color.G
            resultB += color.B
        }

        resultR /= curCombi.size
        resultG /= curCombi.size
        resultB /= curCombi.size
        answer = minOf(answer, abs(goalColor.R - resultR) + abs(goalColor.G - resultG) + abs(goalColor.B - resultB))

        return
    }

    for (i in idx until N) {
        curCombi.add(colors[i].copy())
        combi(i + 1, curCombi, maxDepth)
        curCombi.removeLast()
    }
}

data class Color(val R: Int, val G: Int, val B: Int)
