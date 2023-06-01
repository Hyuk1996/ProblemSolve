fun main() {
    // input
    val n = readln().toInt()

    val arrayA = IntArray(n)
    val arrayB = IntArray(n)
    val arrayC = IntArray(n)
    val arrayD = IntArray(n)
    for (i in 0 until n) {
        val (a, b, c, d) = readln().split(" ").map { it.toInt() }
        arrayA[i] = a
        arrayB[i] = b
        arrayC[i] = c
        arrayD[i] = d
    }

    //solution
    val combOfAB = IntArray(n * n)
    val combOfCD = IntArray(n * n)
    var idx = 0
    for (i in 0 until n) {
        for (j in 0 until n) {
            combOfAB[idx] = arrayA[i] + arrayB[j]
            combOfCD[idx] = arrayC[i] + arrayD[j]
            ++idx
        }
    }

    combOfAB.sort()
    combOfCD.sort()

    var low = 0
    var hi = (n * n) - 1
    var answer = 0L
    while (low < (n * n) && hi > -1) {
        if (combOfAB[low] + combOfCD[hi] == 0) {
            var countOfAB = 1
            while (low < (n * n) - 1 && combOfAB[low] == combOfAB[low + 1]) {
                ++low
                ++countOfAB
            }

            var countOfCD = 1
            while (hi > 0 && combOfCD[hi] == combOfCD[hi - 1]) {
                --hi
                ++countOfCD
            }

            answer += (countOfAB.toLong() * countOfCD)
            ++low
        } else if (combOfAB[low] + combOfCD[hi] > 0) {
            --hi
        } else {
            ++low
        }
    }

    // output
    println(answer)
}
