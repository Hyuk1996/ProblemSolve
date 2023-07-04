fun main() {
    // input
    val N = readln().toInt()
    val a = readln().split(" ").map { it.toInt() }.toIntArray()

    // solution
    var answer = -1
    var cnt = 2
    for (i in 0 until N - 2) {
        if (a[i] <= a[i + 1] && a[i + 1] <= a[i + 2]) {
            cnt = 2
        }
        else if (a[i] >= a[i + 1] && a[i + 1] >= a[i + 2]) {
            cnt = 2
        } else {
            ++cnt
        }
        answer = maxOf(answer, cnt)
    }

    // output
    println(answer)
}
