private var k = 0
private lateinit var arr: CharArray
private lateinit var visited: BooleanArray
private var minValue = 9876543210L
private var maxValue = 0L

fun main() {
    // input
    k = readln().toInt()
    arr = readln().split(" ").map { it[0] }.toCharArray()

    // solution
    visited = BooleanArray(11) { false }
    permutation(mutableListOf())

    // output
    val max = maxValue.toString()
    val min = minValue.toString()
    println("${if (max.length < k) "0$max" else max}")
    println("${if (min.length < k + 1) "0$min" else min}")
}

fun permutation(sequence: MutableList<Int>) {
    if (sequence.size == k + 1) {
        // validate sequence
        var valid = true
        for (i in arr.indices) {
            if (arr[i] == '<') {
                if (sequence[i] > sequence[i + 1]) {
                    valid = false
                    break
                }
            } else {
                if (sequence[i] < sequence[i + 1]) {
                    valid = false
                    break
                }
            }
        }

        if (valid) {
            var value = 0L
            for (no in sequence) {
                value *= 10
                value += no
            }

            maxValue = maxOf(maxValue, value)
            minValue = minOf(minValue, value)
        }
        return
    }

    for (i in 0..9) {
        if (!visited[i]) {
            visited[i] = true
            sequence.add(i)
            permutation(sequence)
            sequence.removeLast()
            visited[i] = false
        }
    }
}
